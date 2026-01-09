#include "jumpNodeEditor.h"

#include <QVBoxLayout>

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../node/node.h"
#include "../../mainInfoWidget/nodeInfoWidget.h"
#include "subWidget/jumpNodeWidgetItem.h"
void JumpNodeEditor::releaseResource( ) {
	size_t count = unionJumpNodeVector.size( );
	auto jumpNodeWidgetItemArrayPtr = unionJumpNodeVector.data( );
	for( size_t index = 0; index < count; ++index )
		delete jumpNodeWidgetItemArrayPtr[ index ];
	unionJumpNodeVector.clear( );
}
bool JumpNodeEditor::createJumpItem( Node *node_ref_link_info ) {

	std::vector< std::vector< Node * > > nodeRefLinkVector;
	if( JumpNodeEditor::JumpWidgetInfoTools::analysisJumpNodeRef( node_ref_link_info, nodeRefLinkVector ) == false )
		return false;
	size_t count = nodeRefLinkVector.size( );
	if( count == 0 )
		return false;
	auto NodesArrayPtr = nodeRefLinkVector.data( );
	size_t index = 0;
	unionJumpNodeVector.resize( count );
	auto jumpNodeWidgetItemArrayPtr = unionJumpNodeVector.data( );
	for( ; index < count; ++index ) {
		auto createItem = new JumpNodeWidgetItem( mainWidget );
		auto itemPen = createItem->getItemPen( );
		itemPen.setColor( QColor( 0, 128, 0 ) );
		itemPen.setWidth( 4 );
		createItem->setItemPen( itemPen );
		itemPen = createItem->getSubItemPen( );
		itemPen.setColor( QColor( 255, 69, 0 ) );
		itemPen.setWidth( 4 );
		createItem->setSubItemPen( itemPen );

		createItem->setIsPopMenu( true );
		createItem->setNodeRefVector( NodesArrayPtr[ index ] );
		mainLayout->addWidget( createItem );
		jumpNodeWidgetItemArrayPtr[ index ] = createItem;
	}
	return true;
}
JumpNodeEditor::JumpNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );

}
bool JumpNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	if( init_node->getNodeType( ) == NodeEnum::NodeType::Point ) {
		std::vector< Node * > jumpNodeVector;
		if( JumpNodeEditor::PointWidgetInfoTools::findJumNodeRef( init_node, jumpNodeVector ) == false )
			return false;
		size_t count = jumpNodeVector.size( );
		auto arrayPtr = jumpNodeVector.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( createJumpItem( arrayPtr[ index ] ) == false ) {
				Application::getInstancePtr( )->getPrinterDirector( )->info( tr( "[%1]节点窗口模块创建异常" ).arg( arrayPtr[ index ]->getNodeTitleName( ) ), Create_SrackInfo( ) );
				return false;
			}
		return true;
	}
	return createJumpItem( init_node );
}

bool JumpNodeEditor::JumpWidgetInfoTools::findPoint( Node *analysis_node_ref_link_info, std::vector< std::pair< Node *, Node * > > &result_input_node_ref_map, std::vector< Node * > &result_node_ref_link_vector ) {

	if( analysis_node_ref_link_info->getNodeType( ) == NodeEnum::NodeType::Point ) {
		result_node_ref_link_vector.emplace_back( analysis_node_ref_link_info );
		return true;
	}
	size_t oldCount = result_input_node_ref_map.size( );
	size_t count = analysis_node_ref_link_info->getThisInputPortRefNodeVector( ).size( );
	auto NodeArrayPtr = analysis_node_ref_link_info->getThisInputPortRefNodeVector( ).data( );

	size_t index = 0;
	for( ; index < count; ++index )
		if( findPoint( NodeArrayPtr[ index ], result_input_node_ref_map, result_node_ref_link_vector ) ) {

			size_t mapCount = result_input_node_ref_map.size( );
			auto mapArrayPtr = result_input_node_ref_map.data( );
			size_t mapIndex = 0;
			for( ; mapIndex < mapCount; ++mapIndex )
				if( mapArrayPtr[ mapIndex ].first == analysis_node_ref_link_info && mapArrayPtr[ mapIndex ].first == NodeArrayPtr[ index ] )
					break;
			if( mapIndex == mapCount )
				result_input_node_ref_map.emplace_back( analysis_node_ref_link_info, NodeArrayPtr[ index ] );
		}
	return oldCount != result_input_node_ref_map.size( );
}
bool JumpNodeEditor::JumpWidgetInfoTools::analysisJumpNodeRef( Node *analysis_node_ref_link_info, std::vector< std::vector< Node * > > &result_node_ref_link_vector ) {

	// 如果不是 jump 节点，即退出
	if( analysis_node_ref_link_info->getNodeType( ) != NodeEnum::NodeType::Jump )
		return false;
	std::vector< Node * > nodePath;
	size_t count = analysis_node_ref_link_info->getThisInputPortRefNodeVector( ).size( );
	auto NodeArrayPtr = analysis_node_ref_link_info->getThisInputPortRefNodeVector( ).data( );
	size_t index = 0;
	std::vector< std::pair< Node *, Node * > > inputNodeRefMap;
	for( ; index < count; ++index ) {
		inputNodeRefMap.emplace_back( analysis_node_ref_link_info, NodeArrayPtr[ index ] );
		if( findPoint( NodeArrayPtr[ index ], inputNodeRefMap, nodePath ) ) {
			size_t mapCount;
			size_t mapIndex;
			std::pair< Node *, Node * > *mapArrayPtr;
			mapCount = inputNodeRefMap.size( );
			mapArrayPtr = inputNodeRefMap.data( );
			std::vector< Node * > jumpVector;
			for( auto item : nodePath ) {
				jumpVector.clear( );
				jumpVector.emplace_back( item );
				while( true ) {
					for( mapIndex = 0; mapIndex < mapCount; ++mapIndex )
						if( mapArrayPtr[ mapIndex ].second == item ) {
							jumpVector.emplace_back( mapArrayPtr[ mapIndex ].first );
							item = mapArrayPtr[ mapIndex ].first;
							break;
						}
					if( mapIndex == mapCount )
						return false; // 匹配异常
					if( mapArrayPtr[ mapIndex ].first == analysis_node_ref_link_info )
						break;
				}
				result_node_ref_link_vector.emplace_back( jumpVector );
			}
			nodePath.clear( );
			inputNodeRefMap.clear( );
		}
	}
	return true;
}
bool JumpNodeEditor::PointWidgetInfoTools::findJumNodeRef( Node *analysis_node_ref_link_info, std::vector< Node * > &result_node_ref_link_vector ) {

	std::vector< Node * > foreachOutNodeRef = analysis_node_ref_link_info->getOutputPortRefThisNodeVector( );
	std::vector< Node * > buffOutNodeRef;
	size_t overCount = result_node_ref_link_vector.size( );
	size_t foreachCount = foreachOutNodeRef.size( );
	auto foreachArrayPtr = foreachOutNodeRef.data( );
	size_t foreachIndex;
	do {
		for( foreachIndex = 0; foreachIndex < foreachCount; ++foreachIndex ) {
			if( foreachArrayPtr[ foreachIndex ]->getNodeType( ) == NodeEnum::NodeType::Jump )
				result_node_ref_link_vector.emplace_back( foreachArrayPtr[ foreachIndex ] );
			else
				buffOutNodeRef.append_range( foreachArrayPtr[ foreachIndex ]->getOutputPortRefThisNodeVector( ) );
		}
		foreachCount = buffOutNodeRef.size( );
		if( foreachCount == 0 )
			break;
		foreachOutNodeRef = buffOutNodeRef;
		foreachArrayPtr = foreachOutNodeRef.data( );
		buffOutNodeRef.clear( );
	} while( true );

	return overCount != result_node_ref_link_vector.size( );
}
