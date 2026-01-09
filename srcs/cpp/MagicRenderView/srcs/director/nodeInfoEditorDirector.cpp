#include "nodeInfoEditorDirector.h"

#include "../app/application.h"
#include "../node/node/node.h"
#include "../node/nodeInfoWidget/editNodeInfoScrollArea/begin/beginNodeEditor.h"
#include "../node/nodeInfoWidget/editNodeInfoScrollArea/generate/intGenerateNodeEditor.h"
#include "../node/nodeInfoWidget/editNodeInfoScrollArea/jump/jumpNodeEditor.h"
#include "../node/nodeInfoWidget/mainInfoWidget/begin/beginNodeWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/generate/intGenerateNodeWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/jump/jumpNodeWidget.h"
#include "../node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h"
#include "../widget/mainWidget.h"
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
	if( create_widget->initNodeInfo( node_ptr ) == false )
		return false;
	return true;
}
void NodeInfoEditorDirector::hide_NodeInfoWidget_signal( NodeInfoWidget *hide_ptr ) {
	if( hide_ptr == nullptr )
		return;
	size_t count = editorWidgetPackage.size( );
	auto nodeInfoWidgetArrayPtr = editorWidgetPackage.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( nodeInfoWidgetArrayPtr[ index ] == hide_ptr ) {
			hide_ptr->deleteLater( );
			editorWidgetPackage.erase( editorWidgetPackage.begin( ) + index );
		}
}
NodeInfoEditorDirector::NodeInfoEditorDirector( ) { }
void NodeInfoEditorDirector::clearNodeEditorResources( ) {

	size_t count = editorWidgetPackage.size( );
	auto nodeInfoWidgetArrayPtr = editorWidgetPackage.data( );
	std::vector< decltype(editorWidgetPackage)::value_type > copyVector( count );
	size_t index;
	auto destArrayPtr = copyVector.data( );
	for( index = 0; index < count; ++index )
		destArrayPtr[ index ] = nodeInfoWidgetArrayPtr[ index ];
	editorWidgetPackage.clear( );
	for( ; index < count; ++index )
		delete destArrayPtr[ index ];
}
NodeInfoEditorDirector::~NodeInfoEditorDirector( ) {
	clearNodeEditorResources( );
}
bool NodeInfoEditorDirector::init( ) {
	instancePtr = Application::getInstancePtr( );
	mainWindow = instancePtr->getMainWindow( );
	mainWidgetScrollArea = mainWindow->getMainWidgetScrollArea( );
	mainWidget = mainWindow->getMainWidget( );
	appendCreateWidget< BeginNodeWidget >( NodeEnum::NodeType::Begin );
	appendCreateWidget< BeginNodeWidget >( NodeEnum::NodeType::End );
	appendCreateWidget< IntGenerateNodeWidget >( NodeEnum::NodeType::Generate );
	appendCreateWidget< JumpNodeWidget >( NodeEnum::NodeType::Jump );
	appendCreateWidget< JumpNodeWidget >( NodeEnum::NodeType::Point );
	return true;
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
		if( nodeInfoWidgetArrayPtr[ index ]->getNode( ) == node_ptr ) {
			result_node_info_editor_widget = nodeInfoWidgetArrayPtr[ index ];
			return true;
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
				result_node_info_editor_widget->setMainWidgetScrollArea( mainWidgetScrollArea );
				editorWidgetPackage.emplace_back( result_node_info_editor_widget );
				connect( result_node_info_editor_widget, &NodeInfoWidget::hide_signal, this, &NodeInfoEditorDirector::hide_NodeInfoWidget_signal );
				result_node_info_editor_widget->move( mainWidget->pos( ) );
				return true;
			}
			break; // 没有找到匹配
		}
	return false;
}
