#include "startNodeEditor.h"

#include <QVBoxLayout>
#include <qcoreevent.h>

#include "../../../../../app/application.h"
#include "../../../../../director/nodeDirector.h"
#include "../../../../../director/printerDirector.h"
#include "../../../../../srack/srackInfo.h"
#include "../../../../../tools/arrayTools.h"
#include "../../../../../tools/vectorTools.h"
#include "../../../../node/imp/beginNodes/startNode.h"
#include "../../../../node/node.h"

#include "startNodeItem.h"

StartNodeEditor::StartNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {

	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	beginItem = new StartNodeItem( mainWidget );
	mainLayout->addWidget( beginItem );
	processItem = new StartNodeItem( mainWidget );
	mainLayout->addWidget( processItem );
	endItem = new StartNodeItem( mainWidget );
	mainLayout->addWidget( endItem );

	auto itemPen = beginItem->getItemPen( );
	itemPen.setColor( QColor( 0, 128, 0 ) );
	itemPen.setWidth( 4 );
	beginItem->setItemPen( itemPen );
	itemPen = beginItem->getSubItemPen( );
	itemPen.setColor( QColor( 255, 69, 0 ) );
	itemPen.setWidth( 4 );
	beginItem->setSubItemPen( itemPen );

	itemPen = processItem->getItemPen( );
	itemPen.setColor( QColor( 255, 165, 0 ) );
	itemPen.setWidth( 4 );
	processItem->setItemPen( itemPen );
	itemPen = processItem->getSubItemPen( );
	itemPen.setColor( QColor( 255, 69, 0 ) );
	itemPen.setWidth( 4 );
	processItem->setSubItemPen( itemPen );

	itemPen = endItem->getItemPen( );
	itemPen.setColor( QColor( 30, 144, 255 ) );
	itemPen.setWidth( 4 );
	endItem->setItemPen( itemPen );
	itemPen = endItem->getSubItemPen( );
	itemPen.setColor( QColor( 255, 69, 0 ) );
	itemPen.setWidth( 4 );
	endItem->setSubItemPen( itemPen );

	beginItem->setIsPopMenu( false );
	endItem->setIsPopMenu( false );
}

StartNodeEditor::~StartNodeEditor( ) {

}
bool StartNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;

	if( init_node->getNodeType( ) == NodeEnum::NodeType::End )
		if( findRefBeginNode( init_node, init_node ) == false )
			return false;
	beginNodePtr = init_node;
	if( beginNodePtr == nullptr )
		return false;
	std::vector< Node * > resultNodeRefLinkVector;
	if( analysisNodeRef( beginNodePtr, resultNodeRefLinkVector ) == false )
		return false;
	if( sortProcessNodeRefArray( resultNodeRefLinkVector, beginNodeRefLinkVector, processNodeRefLinkVector, endNodeRefLinkVector ) == false )
		return false; // 缺少依赖
	beginItem->setNodeRefVector( beginNodeRefLinkVector );
	processItem->setNodeRefVector( processNodeRefLinkVector );
	endItem->setNodeRefVector( endNodeRefLinkVector );
	return true;
}
bool StartNodeEditor::findRefBeginNode( Node *start_find_current_node, Node *&result_begin_node ) {
	auto refOutNodes = start_find_current_node->getOtherNodeOutputPortRefThisNodeInputPortVector( );
	size_t count = refOutNodes.size( );
	if( count == 0 )
		return false;
	auto data = refOutNodes.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->getNodeType( ) == NodeEnum::NodeType::Begin ) {
			result_begin_node = data[ index ];
			return true;
		}
	return false;
}
bool StartNodeEditor::analysisNodeRef( Node *begin_node_ref_link_info, std::vector< Node * > &result_node_ref_link_vector ) {
	if( begin_node_ref_link_info == nullptr )
		return false;
	auto &nodes = begin_node_ref_link_info->getThisNodeOutputPortRefOtherNodeInputPortVector( );
	size_t count = nodes.size( );
	result_node_ref_link_vector.clear( );
	result_node_ref_link_vector.emplace_back( begin_node_ref_link_info );
	if( count == 0 )
		return true;
	result_node_ref_link_vector.append_range( nodes );
	auto arrayPtr = nodes.data( );
	size_t index;

	for( index = 0; index < count; ++index )
		if( analysisOutputPortRefNodeVector( arrayPtr[ index ], result_node_ref_link_vector ) == false )
			return false;
	arrayPtr = result_node_ref_link_vector.data( );
	count = result_node_ref_link_vector.size( );

	std::vector< Node * > buff;
	std::vector< Node * > clone = result_node_ref_link_vector;
	for( index = 0; index < count; ++index )
		if( analysisInputPortRefNodeVector( arrayPtr[ index ], buff ) ) {
			buff.append_range( clone );
			VectorTools::removeRepeat( buff, clone );
			buff.clear( );
		} else
			return false;
	result_node_ref_link_vector = clone;
	return true;
}
bool StartNodeEditor::analysisOutputPortRefNodeVector( Node *foreach_output_port_node, std::vector< Node * > &result_node_ref_link_vector ) {

	auto &nodes = foreach_output_port_node->getThisNodeOutputPortRefOtherNodeInputPortVector( );
	size_t count = nodes.size( );
	if( count == 0 )
		return true;
	result_node_ref_link_vector.append_range( nodes );
	auto arrayPtr = nodes.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( analysisOutputPortRefNodeVector( arrayPtr[ index ], result_node_ref_link_vector ) == false )
			return false;
	return true;
}
bool StartNodeEditor::analysisInputPortRefNodeVector( Node *foreach_output_port_node, std::vector< Node * > &result_node_ref_link_vector ) {

	auto &nodes = foreach_output_port_node->getOtherNodeOutputPortRefThisNodeInputPortVector( );
	size_t count = nodes.size( );
	if( count == 0 )
		return true;
	result_node_ref_link_vector.append_range( nodes );
	auto arrayPtr = nodes.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( analysisInputPortRefNodeVector( arrayPtr[ index ], result_node_ref_link_vector ) == false )
			return false;
	return true;
}
bool StartNodeEditor::sortProcessNodeRefArray( const std::vector< Node * > &sort_vector, std::vector< Node * > &result_begin_vector, std::vector< Node * > &result_process_vector, std::vector< Node * > &result_end_vector ) {
	size_t sortCount = sort_vector.size( );
	if( sortCount == 0 )
		return true; // 不需要排序
	auto copyVector = sort_vector;
	auto sortArray = copyVector.data( );
	size_t index;
	Node *currentSortNode;
	NodeEnum::NodeType nodeType;
	for( index = 0; index < sortCount; ++index ) {
		currentSortNode = sortArray[ index ];
		sortArray[ index ] = nullptr;
		nodeType = currentSortNode->getNodeType( );
		switch( nodeType ) {
			case NodeEnum::NodeType::Begin :
				result_begin_vector.emplace_back( currentSortNode );
				break;
			case NodeEnum::NodeType::End :
				result_end_vector.emplace_back( currentSortNode );
				break;
			case NodeEnum::NodeType::Generate :
			case NodeEnum::NodeType::InterFace :
			case NodeEnum::NodeType::Point :
			case NodeEnum::NodeType::Jump :
			case NodeEnum::NodeType::Logic :
			case NodeEnum::NodeType::Process :
			case NodeEnum::NodeType::Cache :
			case NodeEnum::NodeType::Array :
			case NodeEnum::NodeType::Unity :
				result_process_vector.emplace_back( currentSortNode );
				break;
		}
	}
	Node **buffArrayPtr;
	size_t buffArrayCount;
	// 拷贝开始节点
	buffArrayPtr = result_begin_vector.data( );
	buffArrayCount = result_begin_vector.size( );
	for( index = 0; index < buffArrayCount; ++index )
		sortArray[ index ] = buffArrayPtr[ index ];

	// 排序流程节点
	Node **buffNodeArrayPtr;
	size_t builderNodeIndex;
	size_t outputRefNodeCount;
	size_t outputRefNodeIndex;
	size_t runNodeCount;
	size_t runNodeIndex = index;
	// 拷贝开始节点
	buffNodeArrayPtr = result_process_vector.data( );
	buffArrayCount = result_process_vector.size( );
	Node *findTargetNodePtr;
	const std::vector< Node * > *outputPortRefThisNodeVectorPtr;
	const std::vector< Node * >::value_type *outputRefNodeArray;
	do {
		for( index = 0, builderNodeIndex = 0; builderNodeIndex < buffArrayCount; builderNodeIndex += 1 ) {
			currentSortNode = buffNodeArrayPtr[ builderNodeIndex ];
			outputPortRefThisNodeVectorPtr = &( currentSortNode->getOtherNodeOutputPortRefThisNodeInputPortVector( ) );
			outputRefNodeCount = outputPortRefThisNodeVectorPtr->size( );
			if( outputRefNodeCount ) {
				outputRefNodeArray = outputPortRefThisNodeVectorPtr->data( );
				outputRefNodeIndex = 0, runNodeCount = 0;
				while( outputRefNodeIndex < outputRefNodeCount ) {
					findTargetNodePtr = outputRefNodeArray[ outputRefNodeIndex ];
					if( ArrayTools::findIndex( sortArray, runNodeIndex, findTargetNodePtr, runNodeCount ) == false ) {
						break;
					}
					outputRefNodeIndex += 1;
					runNodeCount = 0;
				}
				if( outputRefNodeIndex != outputRefNodeCount )
					continue;
			}
			sortArray[ runNodeIndex ] = currentSortNode;
			runNodeIndex += 1;
			index += 1;
			buffNodeArrayPtr[ builderNodeIndex ] = nullptr;
		}
		if( index == buffArrayCount )
			break;// 不需要排序
		if( index == 0 ) { // 没有进行改变
			Application *instancePtr = Application::getInstancePtr( );
			NodeDirector *nodeDirector = instancePtr->getNodeDirector( );
			auto arrayToString = nodeDirector->nodeArrayToString( buffNodeArrayPtr, index );
			auto orgToString = nodeDirector->nodeArrayToString( sortArray, sortCount );
			QString form( "发现未知依赖节点:\n\t%1\n原始:\t%2" );
			instancePtr->getPrinterDirector( )->info( form.arg( arrayToString ).arg( orgToString ), Create_SrackInfo( ) );
			return false;
		}
		ArrayTools::sortNullptr( buffNodeArrayPtr, buffArrayCount );
		buffArrayCount -= index;// 重置大小
	} while( true );
	// 调整进程序列
	index = result_begin_vector.size( ); // 跳过开始节点
	buffArrayCount = result_process_vector.size( );
	sortArray += index;
	for( builderNodeIndex = 0; builderNodeIndex < buffArrayCount; builderNodeIndex += 1 )
		buffNodeArrayPtr[ builderNodeIndex ] = sortArray[ builderNodeIndex ];
	return true;
}
void StartNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	beginNodeRefLinkVector.clear( );
	processNodeRefLinkVector.clear( );
	endNodeRefLinkVector.clear( );
	beginNodePtr = nullptr;
}
