#include "nodeRunLink.h"

#include "../nodeRunLinkData.h"

#include "../../../enums/nodeEnum.h"

#include "../../../tools/NodeRunLinkTools.h"
#include "../../../tools/arrayTools.h"
#include "../../../tools/vectorTools.h"

#include "../../node/node.h"

NodeRunLink::~NodeRunLink( ) {
	delete get;
	delete nodeRunLinkData;
}
NodeRunLink::NodeRunLink( Node *const init_node_ptr ) {
	nodeRunLinkData = new NodeRunLinkData( init_node_ptr );
	get = new NodeRunLinkTools::Get( nodeRunLinkData );
	currentOver = nullptr;
	empty = true;
}
bool NodeRunLink::getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr ) {
	if( nodeRunLinkData->over )
		return false;
	if( currentOver && currentOver != nodeRunLinkData->currentNode ) {
		result_next_node_ptr = nodeRunLinkData->currentNode;
		return true;
	}
	size_t overCount;
	size_t beginCount;
	size_t beginIndex;
	size_t overIndex;
	Node **beginData;
	Node *const*overData;

	// 完整调用开始节点
	beginCount = nodeRunLinkData->startNodeVector.size( );
	if( beginCount == 0 )
		return false; // 不存在开始
	beginData = nodeRunLinkData->startNodeVector.data( );
	// 如果未开始
	if( nodeRunLinkData->currentNode == nullptr ) {
		nodeRunLinkData->currentNode = result_next_node_ptr = beginData[ 0 ];
		return true;
	}
	for( beginIndex = 0; beginIndex < beginCount; ++beginIndex )
		if( nodeRunLinkData->currentNode == beginData[ beginIndex ] ) {
			++beginIndex;
			if( beginIndex == beginCount )
				break; // 末尾，跳出
			nodeRunLinkData->currentNode = result_next_node_ptr = beginData[ beginIndex ];
			return true;
		}
	// 检查当前节点是否在完成列表但空中
	overCount = nodeRunLinkData->overRunNodeVector.size( );
	if( overCount ) {
		overData = nodeRunLinkData->overRunNodeVector.data( );
		for( overIndex = 0; overIndex < overCount; ++overIndex )
			if( overData[ overIndex ] == nodeRunLinkData->currentNode )
				break;

		if( overIndex == overCount ) {
			overCount = over_run_node_vector.size( );
			if( overCount == 0 )
				return false;
			overData = over_run_node_vector.data( );

			for( overIndex = 0; overIndex < overCount; ++overIndex )
				if( overData[ overIndex ] == nodeRunLinkData->currentNode )
					break;
			if( overIndex == overCount )
				return false; // 不在匹配当中
		}
	}

	auto &adviseNodeVector = get->getAdviseNodeVector( );
	auto iterator = adviseNodeVector.begin( );
	auto end = adviseNodeVector.end( );
	for( ; iterator != end; ++iterator ) {
		Node *node = *iterator;
		auto &refThisNodeInputPortVector = node->getOtherNodeOutputPortRefThisNodeInputPortVector( );
		size_t refCount = refThisNodeInputPortVector.size( );
		auto refData = refThisNodeInputPortVector.data( );
		size_t findIndex;
		for( findIndex = 0; findIndex < refCount; ++findIndex ) {
			NodeEnum::NodeType nodeType = refData[ findIndex ]->getNodeType( );
			if( nodeType == NodeEnum::NodeType::Point )
				continue; // 跳转节点，不需要运行
			overData = nodeRunLinkData->overRunNodeVector.data( );
			for( overIndex = 0; overIndex < overCount; ++overIndex )
				if( overData[ overIndex ] == nodeRunLinkData->currentNode )
					break;
			if( overIndex < overCount )
				continue; // 已经匹配

			overCount = over_run_node_vector.size( );
			if( overCount == 0 )
				break; // 不存在
			overData = over_run_node_vector.data( );

			for( overIndex = 0; overIndex < overCount; ++overIndex )
				if( overData[ overIndex ] == nodeRunLinkData->currentNode )
					break;
			if( overIndex == overCount )
				break; // 不存在
		}
		if( findIndex < refCount )
			continue;
		nodeRunLinkData->currentNode = result_next_node_ptr = node;
		adviseNodeVector.erase( iterator );
		return true;
	}
	return false;
}
bool NodeRunLink::runRunNode( const QDateTime &run_time, size_t run_frame ) {
	if( nodeRunLinkData->currentNode == nullptr )
		return false;

	bool fillNodeCall = nodeRunLinkData->currentNode->fillNodeCall( run_time, run_frame );
	if( fillNodeCall == true ) {
		size_t find = 0;
		if( VectorTools::findIndex( nodeRunLinkData->overRunNodeVector, nodeRunLinkData->currentNode, find ) == false )
			nodeRunLinkData->overRunNodeVector.emplace_back( nodeRunLinkData->currentNode );
		std::vector< Node * > nextRunAdviseNodeVector;
		if( nodeRunLinkData->currentNode->fillOutputPortCall( run_time, run_frame, nextRunAdviseNodeVector ) )
			nodeRunLinkData->adviseNodeVector.append_range( nextRunAdviseNodeVector );
		find = nodeRunLinkData->adviseNodeVector.size( );
		if( find == 0 )
			nodeRunLinkData->over = true;
		currentOver = nodeRunLinkData->currentNode;
	}
	return fillNodeCall;
}

bool NodeRunLink::adviseRunNode( const Node *const node ) const {
	return nodeRunLinkData->adviseRunNode( node );
}
bool NodeRunLink::filterDeprecatedNode( std::vector< Node * > &filter_target_ref_src_vector ) {

	size_t count = filter_target_ref_src_vector.size( );
	if( count == 0 )
		return true;
	auto data = filter_target_ref_src_vector.data( );
	if( data == nullptr )
		return true;
	size_t index = 0;
	size_t buffIndex;
	while( index < count )
		if( data[ index ] == nullptr ) {
			buffIndex = index;
			count -= 1;
			for( ; buffIndex < count; buffIndex++ )
				data[ buffIndex ] = data[ buffIndex + 1 ];
		} else
			switch( data[ index ]->getNodeType( ) ) {
				case NodeEnum::NodeType::Call :
				case NodeEnum::NodeType::Function :
				case NodeEnum::NodeType::Jump :
				case NodeEnum::NodeType::Point :
					buffIndex = index;
					count -= 1;
					for( ; buffIndex < count; buffIndex++ )
						data[ buffIndex ] = data[ buffIndex + 1 ];
					break;
				default :
					++index;
					break;
			}
	if( buffIndex == count )
		filter_target_ref_src_vector.resize( count );
	return true;
}
const std::list< Node * > & NodeRunLink::getAdviseNodeVector( ) const {
	return nodeRunLinkData->adviseNodeVector;
}
Node * NodeRunLink::getBeforeNode( ) const {
	return nodeRunLinkData->beforeNode;
}
Node * NodeRunLink::getCurrentNode( ) const {
	return nodeRunLinkData->currentNode;
}
const std::vector< Node * > & NodeRunLink::getLinkNodeVector( ) const {
	return nodeRunLinkData->linkNodeVector;
}
const std::vector< Node * > & NodeRunLink::getOverRunNodeVector( ) const {
	return nodeRunLinkData->overRunNodeVector;
}
const std::vector< Node * > & NodeRunLink::getStartNodeVector( ) const {
	return nodeRunLinkData->startNodeVector;
}
bool NodeRunLink::linkHasStartNode( const Node *const check_start_node_ptr ) const {
	return nodeRunLinkData->linkHasStartNode( check_start_node_ptr );
}
bool NodeRunLink::isOver( ) const {
	return nodeRunLinkData->over;
}
bool NodeRunLink::isReady( ) const {
	return nodeRunLinkData->ready;
}
bool NodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return nodeRunLinkData->linkHasNode( check_node_ptr );
}
bool NodeRunLink::linkHasEndNode( const Node *const check_node_ptr ) const {
	return nodeRunLinkData->linkHasNode( check_node_ptr );
}
bool NodeRunLink::sortBilderList( const std::vector< Node * > &reference_sort_vector ) {
	size_t startCount = nodeRunLinkData->linkNodeVector.size( );
	if( startCount == 0 )
		return false;
	size_t refCount = reference_sort_vector.size( );
	if( refCount == 0 )
		return false;
	auto sortData = nodeRunLinkData->linkNodeVector.data( );

	std::vector< Node * > *buff;
	buff = new std::vector< Node * >( startCount );
	auto refData = reference_sort_vector.data( );

	auto buffData = buff->data( );
	size_t buffIndex = 0;

	size_t startIndex;
	size_t refIndex;

	for( startIndex = 0, refIndex = 0; refIndex < refCount; ++refIndex, startIndex = 0 )
		if( ArrayTools::findIndex( sortData, startCount, refData[ refIndex ], startIndex ) == true ) {
			if( buffIndex == startCount ) {
				delete buff;
				return false;
			}
			buffData[ buffIndex ] = refData[ refIndex ];
			++buffIndex;
		}
	for( refIndex = 0; refIndex < startCount; ++refIndex )
		sortData[ refIndex ] = buffData[ refIndex ];
	delete buff;
	nodeRunLinkData->overRunNodeVector.clear( );
	nodeRunLinkData->startNodeVector.clear( );
	return true;
}
