#include "nodeInfoEditorDirector.h"

#include <QScrollBar>

#include "../app/application.h"
#include "../node/node/node.h"
#include "../node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h"
#include "../widget/mainWidgetScrollArea.h"
#include "../win/mainWindow.h"
bool NodeInfoEditorDirector::appendCreateWidget( MTKey key, const MTCreateFunction &create_function ) {
	size_t count;
	MTVector< MTKey, MTValue< MTCreateFunction > >::value_type *mapArrayPtr;
	MTValue< MTCreateFunction > *mtVector;
	size_t index;
	if( create_function == nullptr )
		return false;
	count = generaterNodeInfoEditorWidgetMap.size( );
	if( count != 0 ) {
		mapArrayPtr = generaterNodeInfoEditorWidgetMap.data( );
		for( index = 0; index < count; ++index )
			if( mapArrayPtr[ index ].first == key ) {
				mapArrayPtr[ index ].second.emplace_back( create_function );
				return true; // 没有找到匹配
			}
	}
	mtVector = new MTValue< MTCreateFunction >( );
	mtVector->emplace_back( create_function );
	generaterNodeInfoEditorWidgetMap.emplace_back( key, *mtVector );
	delete mtVector;
	return true;
}
bool NodeInfoEditorDirector::checkCreateWidget( Node *node_ptr, NodeInfoWidget *create_widget ) {
	if( create_widget->checkNodeValid( node_ptr ) == false )
		return false;
	return true;
}
void NodeInfoEditorDirector::hide_NodeInfoWidget_signal( NodeInfoWidget *hide_ptr ) {
	//clearNodeEditorResources( );
}
NodeInfoEditorDirector::NodeInfoEditorDirector( ) { }
void NodeInfoEditorDirector::clearNodeEditorResources( ) {
	using vector = std::vector< decltype(editorWidgetPackage)::value_type >;
	vector *copyVector;
	vector *releaseVector;
	NodeInfoWidget **nodeInfoWidgetArrayPtr;
	NodeInfoWidget **releaseArrayPtr;
	NodeInfoWidget **destArrayPtr;
	size_t count;
	size_t index;
	size_t destArrayPtrIndex;
	size_t releaseArrayPtrIndex;
	count = editorWidgetPackage.size( );
	if( count == 0 )
		return;
	nodeInfoWidgetArrayPtr = editorWidgetPackage.data( );
	copyVector = new vector( count );
	releaseVector = new vector( count );
	destArrayPtrIndex = 0;
	releaseArrayPtrIndex = 0;
	destArrayPtr = copyVector->data( );
	releaseArrayPtr = releaseVector->data( );
	for( index = 0; index < count; ++index )
		if( nodeInfoWidgetArrayPtr[ index ] ) {
			if( nodeInfoWidgetArrayPtr[ index ]->isHidden( ) == true ) {
				releaseArrayPtr[ releaseArrayPtrIndex ] = nodeInfoWidgetArrayPtr[ index ];
				releaseArrayPtrIndex += 1;
				continue;
			}
			destArrayPtr[ destArrayPtrIndex ] = nodeInfoWidgetArrayPtr[ index ];
			destArrayPtrIndex += 1;
		}
	// 清理
	editorWidgetPackage.clear( );
	// 删除个数
	if( releaseArrayPtrIndex )
		for( index = 0; index < releaseArrayPtrIndex; ++index )
			delete releaseArrayPtr[ index ];
	// 重新保存个数
	if( destArrayPtrIndex ) {
		editorWidgetPackage.resize( destArrayPtrIndex );
		nodeInfoWidgetArrayPtr = editorWidgetPackage.data( );
		for( index = 0; index < destArrayPtrIndex; ++index )
			nodeInfoWidgetArrayPtr[ index ] = destArrayPtr[ index ];
	}
	// 释放
	delete copyVector;
	delete releaseVector;
}
void NodeInfoEditorDirector::releaseNodeEditor( ) {
	using vector = std::vector< decltype(editorWidgetPackage)::value_type >;
	size_t count;
	NodeInfoWidget **nodeInfoWidgetArrayPtr;
	vector *copyVector;
	size_t index;
	size_t destArrayPtrIndex;
	NodeInfoWidget **destArrayPtr;

	count = editorWidgetPackage.size( );
	if( count == 0 )
		return;;
	nodeInfoWidgetArrayPtr = editorWidgetPackage.data( );
	copyVector = new vector( count );
	destArrayPtrIndex = 0;
	destArrayPtr = copyVector->data( );
	for( index = 0; index < count; ++index )
		if( nodeInfoWidgetArrayPtr[ index ] ) {
			destArrayPtr[ destArrayPtrIndex ] = nodeInfoWidgetArrayPtr[ index ];
			destArrayPtrIndex += 1;
		}
	editorWidgetPackage.clear( );
	for( index = 0; index < destArrayPtrIndex; ++index )
		delete destArrayPtr[ index ];
	delete copyVector;
}
NodeInfoEditorDirector::~NodeInfoEditorDirector( ) {
	releaseNodeEditor( );
}
bool NodeInfoEditorDirector::init( ) {
	releaseNodeEditor( );
	instancePtr = Application::getInstancePtr( );
	mainWindow = instancePtr->getMainWindow( );
	mainWidgetScrollArea = mainWindow->getMainWidgetScrollArea( );
	mainWidget = mainWindow->getMainWidget( );
	/*appendCreateWidget< StartNodeWidget >( NodeEnum::NodeType::Begin );
	appendCreateWidget< StartNodeWidget >( NodeEnum::NodeType::End );
	appendCreateWidget< IntGenerateNodeWidget >( NodeEnum::NodeType::Generate );
	appendCreateWidget< UIntGenerateNodeWidget >( NodeEnum::NodeType::Generate );
	appendCreateWidget< FloatGenerateNodeWidget >( NodeEnum::NodeType::Generate );
	appendCreateWidget< BinGenerateNodeWidget >( NodeEnum::NodeType::Generate );
	appendCreateWidget< StringGenerateNodeWidget >( NodeEnum::NodeType::Generate );
	appendCreateWidget< CharGenerateNodeWidget >( NodeEnum::NodeType::Generate );*/
	return true;
}
void NodeInfoEditorDirector::appendEditorWidgetPackage( NodeInfoWidget *node_info_widget ) {
	if( node_info_widget == nullptr )
		return;
	size_t count = editorWidgetPackage.size( );
	NodeInfoWidget **nodeInfoWidgetArrayPtr;
	size_t index;
	if( count ) {
		nodeInfoWidgetArrayPtr = editorWidgetPackage.data( );
		for( index = 0; index < count; ++index )
			if( nodeInfoWidgetArrayPtr[ index ] == node_info_widget )
				return;
		for( index = 0; index < count; ++index )
			if( nodeInfoWidgetArrayPtr[ index ] == nullptr ) {
				nodeInfoWidgetArrayPtr[ index ] = node_info_widget;
				return;
			}
	}
	auto viewport = mainWidgetScrollArea->viewport( );
	QSize cureateWidgetSizet = viewport->size( );
	int width = cureateWidgetSizet.width( );
	width = width / 3;
	QPoint point( width, 0 );
	point = viewport->mapToGlobal( point );
	node_info_widget->move( point );
	cureateWidgetSizet.setWidth( width );
	QScrollBar *verticalScrollBar = mainWidgetScrollArea->horizontalScrollBar( );
	int newHeight;
	if( verticalScrollBar ) {
		newHeight = cureateWidgetSizet.height( ) - verticalScrollBar->height( );
		if( newHeight > 0 )
			cureateWidgetSizet.setHeight( newHeight );
		else
			cureateWidgetSizet.setHeight( 0 );
	}
	node_info_widget->resize( cureateWidgetSizet );
	editorWidgetPackage.emplace_back( node_info_widget );
}
bool NodeInfoEditorDirector::getNodeInfoEditorWidget( Node *node_ptr, NodeInfoWidget *&result_node_info_editor_widget ) {
	size_t count;
	MTVector< MTKey, MTValue< MTCreateFunction > >::value_type *mapArrayPtr;
	MTValue< MTCreateFunction >::value_type *arrayPtr;
	size_t index;
	MTKey nodeType;
	NodeInfoWidget **nodeInfoWidgetArrayPtr;
	if( node_ptr == nullptr )
		return false;

	// 遍历已经保存的列表
	count = editorWidgetPackage.size( );
	nodeInfoWidgetArrayPtr = editorWidgetPackage.data( );
	for( index = 0; index < count; ++index )
		if( nodeInfoWidgetArrayPtr[ index ] == nullptr )
			continue;
		else if( nodeInfoWidgetArrayPtr[ index ]->getNode( ) == node_ptr ) {
			result_node_info_editor_widget = nodeInfoWidgetArrayPtr[ index ];
			return true;
		}
	// 获取窗口
	result_node_info_editor_widget = node_ptr->getNodeInfoWidget( );
	if( result_node_info_editor_widget )
		if( result_node_info_editor_widget->checkNodeValid( node_ptr ) ) {
			appendEditorWidgetPackage( result_node_info_editor_widget );
			connect( result_node_info_editor_widget, &NodeInfoWidget::hide_signal, this, &NodeInfoEditorDirector::hide_NodeInfoWidget_signal );
			return true;
		} else {
			delete result_node_info_editor_widget;
			result_node_info_editor_widget = nullptr;
		}
	// 遍历创建调用
	count = generaterNodeInfoEditorWidgetMap.size( );
	if( count == 0 )
		return false;

	mapArrayPtr = generaterNodeInfoEditorWidgetMap.data( );
	for( index = 0; index < count; ++index )
		if( nodeType = node_ptr->getNodeType( ), mapArrayPtr[ index ].first == nodeType ) {
			count = mapArrayPtr[ index ].second.size( );
			arrayPtr = mapArrayPtr[ index ].second.data( );
			for( index = 0; index < count; ++index ) {
				result_node_info_editor_widget = arrayPtr[ index ].operator()( node_ptr );
				if( result_node_info_editor_widget == nullptr )
					continue; // 失败，继续下一个
				appendEditorWidgetPackage( result_node_info_editor_widget );
				connect( result_node_info_editor_widget, &NodeInfoWidget::hide_signal, this, &NodeInfoEditorDirector::hide_NodeInfoWidget_signal );
				return true;
			}
			break; // 没有找到匹配
		}
	return false;
}
