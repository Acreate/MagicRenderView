#include "beginNodeEditor.h"

#include <QVBoxLayout>
#include <qcoreevent.h>

#include "../../../../app/application.h"

#include "../../../../director/nodeDirector.h"
#include "../../../../director/printerDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../../tools/arrayTools.h"
#include "../../../../tools/vectorTools.h"

#include "../../../node/node.h"

#include "../../mainInfoWidget/nodeInfoWidget.h"

#include "subWidget/beginNodeItem.h"

BeginNodeEditor::BeginNodeEditor( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	leftWidget = nullptr;
	rightWidget = nullptr;
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
	beginItem = new BeginNodeItem( mainWidget );
	mainLayout->addWidget( beginItem );
	processItem = new BeginNodeItem( mainWidget );
	mainLayout->addWidget( processItem );
	endItem = new BeginNodeItem( mainWidget );
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

BeginNodeEditor::~BeginNodeEditor( ) {

}
bool BeginNodeEditor::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;

	beginNodeRefLinkInfo = init_node;
	if( init_node->getNodeType( ) == NodeEnum::NodeType::End )
		if( findRefBeginNode( beginNodeRefLinkInfo, beginNodeRefLinkInfo ) == false )
			return false;
	std::vector< Node * > resultNodeRefLinkVector;
	if( analysisNodeRef( beginNodeRefLinkInfo, resultNodeRefLinkVector ) == false )
		return false;
	size_t count = resultNodeRefLinkVector.size( );
	auto nodeRefLinkInfoArrayPtr = resultNodeRefLinkVector.data( );
	if( sortProcessNodeRefArray( nodeRefLinkInfoArrayPtr, count ) == false )
		return false; // 缺少依赖
	beginItem->setNodeRefVector( beginNodeRefLinkVector );
	processItem->setNodeRefVector( processNodeRefLinkVector );
	endItem->setNodeRefVector( endNodeRefLinkVector );
	return true;
}
bool BeginNodeEditor::findRefBeginNode( Node *start_find_current_node, Node *&result_begin_node ) {
	auto refOutNodes = start_find_current_node->getOutputPortRefThisNodeVector( );
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
bool BeginNodeEditor::analysisNodeRef( Node *begin_node_ref_link_info, std::vector< Node * > &result_node_ref_link_vector ) {
	if( begin_node_ref_link_info == nullptr )
		return false;
	auto &nodes = begin_node_ref_link_info->getThisInputPortRefNodeVector( );
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
bool BeginNodeEditor::analysisOutputPortRefNodeVector( Node *foreach_output_port_node, std::vector< Node * > &result_node_ref_link_vector ) {

	auto &nodes = foreach_output_port_node->getThisInputPortRefNodeVector( );
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
bool BeginNodeEditor::analysisInputPortRefNodeVector( Node *foreach_output_port_node, std::vector< Node * > &result_node_ref_link_vector ) {

	auto &nodes = foreach_output_port_node->getOutputPortRefThisNodeVector( );
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
bool BeginNodeEditor::sortProcessNodeRefArray( const std::vector< Node * >::pointer &sort_target_array_ptr, const size_t &sort_target_array_count ) {
	if( sort_target_array_ptr == nullptr )
		return false; // 数组不可访问
	if( sort_target_array_count == 0 )
		return true; // 不需要排序
	// 开始节点
	std::vector< Node * > beginVector;
	// 结束节点
	std::vector< Node * > endVector;
	// 分配流程
	std::vector< Node * > processVector;

	size_t index;
	Node *currentSortNode;
	NodeEnum::NodeType nodeType;
	for( index = 0; index < sort_target_array_count; ++index ) {
		currentSortNode = sort_target_array_ptr[ index ];
		sort_target_array_ptr[ index ] = nullptr;
		nodeType = currentSortNode->getNodeType( );
		switch( nodeType ) {
			case NodeEnum::NodeType::Begin :
				beginVector.emplace_back( currentSortNode );
				break;
			case NodeEnum::NodeType::End :
				endVector.emplace_back( currentSortNode );
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
				processVector.emplace_back( currentSortNode );
				break;
		}
	}
	Node **buffArrayPtr;
	size_t buffArrayCount;
	// 拷贝开始节点
	buffArrayPtr = beginVector.data( );
	buffArrayCount = beginVector.size( );
	for( index = 0; index < buffArrayCount; ++index )
		sort_target_array_ptr[ index ] = buffArrayPtr[ index ];

	// 排序流程节点

	Node **buffNodeArrayPtr;
	size_t builderNodeIndex;
	size_t sortArrayCount;
	size_t outputRefNodeCount;
	size_t outputRefNodeIndex;
	size_t runNodeCount;
	size_t runNodeIndex = index;
	// 拷贝开始节点
	buffNodeArrayPtr = processVector.data( );
	sortArrayCount = processVector.size( );
	const std::vector< Node * > *outputPortRefThisNodeVectorPtr;
	const std::vector< Node * >::value_type *outputRefNodeArray;
	do {
		for( builderNodeIndex = 0; builderNodeIndex < sortArrayCount; builderNodeIndex += 1 ) {
			currentSortNode = buffNodeArrayPtr[ builderNodeIndex ];
			outputPortRefThisNodeVectorPtr = &( currentSortNode->getOutputPortRefThisNodeVector( ) );
			outputRefNodeCount = outputPortRefThisNodeVectorPtr->size( );
			outputRefNodeArray = outputPortRefThisNodeVectorPtr->data( );
			outputRefNodeIndex = 0, runNodeCount = 0;
			while( outputRefNodeIndex < outputRefNodeCount ) {
				if( ArrayTools::findIndex( sort_target_array_ptr, runNodeIndex, outputRefNodeArray[ outputRefNodeIndex ], runNodeCount ) == false )
					break;
				outputRefNodeIndex += 1;
				runNodeCount = 0;
			}
			if( outputRefNodeIndex != outputRefNodeCount )
				continue;
			sort_target_array_ptr[ runNodeIndex ] = currentSortNode;
			runNodeIndex += 1;
			buffNodeArrayPtr[ builderNodeIndex ] = nullptr;
		}
		if( runNodeIndex == sort_target_array_count )
			break;// 不需要排序
		index = sort_target_array_count - runNodeIndex; // 剩余个数
		if( index == sortArrayCount ) { // 没有进行改变
			Application *instancePtr = Application::getInstancePtr( );
			auto arrayToString = instancePtr->getNodeDirector( )->nodeArrayToString( buffNodeArrayPtr, index );
			QString form( "发现未知依赖节点:\n\t%1" );
			instancePtr->getPrinterDirector( )->info( form.arg( arrayToString ), Create_SrackInfo( ) );
			return false;
		}
		ArrayTools::sortNullptr( buffNodeArrayPtr, sortArrayCount );
		sortArrayCount -= index;// 重置大小
	} while( true );

	return true;
}
void BeginNodeEditor::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
	beginNodeRefLinkVector.clear( );
	processNodeRefLinkVector.clear( );
	endNodeRefLinkVector.clear( );
	beginNodeRefLinkInfo = nullptr;
}
