#include "NodeRunLinkTools.h"

#include "arrayTools.h"

#include "../node/node/node.h"
#include "../node/nodeRunInfo/nodeRunLinkData.h"
std::vector< Node * > & NodeRunLinkTools::Get::getAdviseNodeVector( ) const {
	return nodeRunLinkData->adviseNodeVector;
}
std::vector< Node * > & NodeRunLinkTools::Get::getLinkNodeVector( ) const {
	return nodeRunLinkData->linkNodeVector;
}
std::vector< Node * > & NodeRunLinkTools::Get::getOverRunNodeVector( ) const {
	return nodeRunLinkData->overRunNodeVector;
}
std::vector< Node * > & NodeRunLinkTools::Get::getStartNodeVector( ) const {
	return nodeRunLinkData->startNodeVector;
}
bool NodeRunLinkTools::Get::getNodeRef( std::vector< Node * > &result_ref_node_vector ) {
	return NodeRunLinkTools::getNodeRef( nodeRunLinkData->beforeNode, result_ref_node_vector );
}
bool NodeRunLinkTools::Get::getNodeInputInForRef( std::vector< Node * > &result_ref_node_vector ) {
	return NodeRunLinkTools::getNodeInputInForRef( nodeRunLinkData->beforeNode, result_ref_node_vector );
}
bool NodeRunLinkTools::Get::getNodeOutputInForRef( std::vector< Node * > &result_ref_node_vector ) {
	return NodeRunLinkTools::getNodeOutputInForRef( nodeRunLinkData->beforeNode, result_ref_node_vector );
}

bool NodeRunLinkTools::getNodeRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	if( get_node_target == nullptr )
		return false;
	std::list< Node * > topJobStack;
	std::list< Node * >::iterator iterator;
	size_t resultCount = result_ref_node_vector.size( );
	auto resuktData = result_ref_node_vector.data( );
	size_t findResult;
	size_t appendCount;
	Node *const*appendData;
	size_t appendIndex;
	do {
		findResult = 0;
		if( ArrayTools::findIndex( resuktData, resultCount, get_node_target, findResult ) == false ) {
			// 加入返回
			result_ref_node_vector.emplace_back( get_node_target );
			resultCount = result_ref_node_vector.size( );
			resuktData = result_ref_node_vector.data( );
			// 输出依赖
			auto &thisOutRefNode = get_node_target->getThisNodeOutputPortRefOtherNodeInputPortVector( );
			appendCount = thisOutRefNode.size( );
			appendData = thisOutRefNode.data( );
			for( findResult = appendIndex = 0; appendIndex < appendCount; ++appendIndex, findResult = 0 )
				if( ArrayTools::findIndex( resuktData, resultCount, appendData[ appendIndex ], findResult ) == false )
					topJobStack.emplace_front( appendData[ appendIndex ] );
			// 输入依赖
			auto &thisInRefNode = get_node_target->getOtherNodeOutputPortRefThisNodeInputPortVector( );
			appendCount = thisInRefNode.size( );
			appendData = thisInRefNode.data( );
			for( findResult = appendIndex = 0; appendIndex < appendCount; ++appendIndex, findResult = 0 )
				if( ArrayTools::findIndex( resuktData, resultCount, appendData[ appendIndex ], findResult ) == false )
					topJobStack.emplace_front( appendData[ appendIndex ] );
		}
		if( topJobStack.empty( ) )
			return true;
		iterator = topJobStack.begin( );
		get_node_target = *iterator;
		if( get_node_target == nullptr )
			return false;
		topJobStack.erase( iterator );
	} while( true );
	return true;
}
bool NodeRunLinkTools::sortNodeRef( const std::vector< Node * > &ref_sort_node_vector, std::vector< Node * > &result_ref_node_vector ) {
	std::vector< Node * > begin;
	size_t count;
	count = ref_sort_node_vector.size( );
	if( count == 0 )
		return false;
	auto data = ref_sort_node_vector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->getOtherNodeOutputPortRefThisNodeInputPortVector( ).size( ) == 0 )
			begin.emplace_back( data[ index ] );
	if( begin.size( ) == 0 )
		return false;
	return sortNodeRef( begin, ref_sort_node_vector, result_ref_node_vector );
}
bool NodeRunLinkTools::sortNodeRef( const std::vector< Node * > &ref_begin_sort_node_vector, const std::vector< Node * > &ref_sort_node_vector, std::vector< Node * > &result_ref_node_vector ) {
	size_t count;
	count = ref_begin_sort_node_vector.size( );
	if( count == 0 )
		return false;
	size_t refSortCount = ref_sort_node_vector.size( );
	result_ref_node_vector.resize( refSortCount );
	// todo:排序
	return false;
}
bool NodeRunLinkTools::getNodeInputInForRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	if( get_node_target == nullptr )
		return false;
	std::list< Node * > topJobStack;
	std::list< Node * >::iterator iterator;
	size_t resultCount = result_ref_node_vector.size( );
	auto resuktData = result_ref_node_vector.data( );
	size_t findResult;
	size_t appendCount;
	Node *const*appendData;
	size_t appendIndex;
	do {
		findResult = 0;
		if( ArrayTools::findIndex( resuktData, resultCount, get_node_target, findResult ) == false ) {
			// 加入返回
			result_ref_node_vector.emplace_back( get_node_target );
			resultCount = result_ref_node_vector.size( );
			resuktData = result_ref_node_vector.data( );
			// 输入依赖
			auto &thisInRefNode = get_node_target->getOtherNodeOutputPortRefThisNodeInputPortVector( );
			appendCount = thisInRefNode.size( );
			appendData = thisInRefNode.data( );
			for( findResult = appendIndex = 0; appendIndex < appendCount; ++appendIndex, findResult = 0 )
				if( ArrayTools::findIndex( resuktData, resultCount, appendData[ appendIndex ], findResult ) == false )
					topJobStack.emplace_front( appendData[ appendIndex ] );
		}
		if( topJobStack.empty( ) )
			return true;
		iterator = topJobStack.begin( );
		get_node_target = *iterator;
		if( get_node_target == nullptr )
			return false;
		topJobStack.erase( iterator );
	} while( true );
	return true;
}
bool NodeRunLinkTools::getNodeOutputInForRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	if( get_node_target == nullptr )
		return false;
	std::list< Node * > topJobStack;
	std::list< Node * >::iterator iterator;
	size_t resultCount = result_ref_node_vector.size( );
	auto resuktData = result_ref_node_vector.data( );
	size_t findResult;
	size_t appendCount;
	Node *const*appendData;
	size_t appendIndex;
	do {
		findResult = 0;
		if( ArrayTools::findIndex( resuktData, resultCount, get_node_target, findResult ) == false ) {
			// 加入返回
			result_ref_node_vector.emplace_back( get_node_target );
			resultCount = result_ref_node_vector.size( );
			resuktData = result_ref_node_vector.data( );
			// 输出依赖
			auto &thisOutRefNode = get_node_target->getThisNodeOutputPortRefOtherNodeInputPortVector( );
			appendCount = thisOutRefNode.size( );
			appendData = thisOutRefNode.data( );
			for( findResult = appendIndex = 0; appendIndex < appendCount; ++appendIndex, findResult = 0 )
				if( ArrayTools::findIndex( resuktData, resultCount, appendData[ appendIndex ], findResult ) == false )
					topJobStack.emplace_front( appendData[ appendIndex ] );
		}
		if( topJobStack.empty( ) )
			return true;
		iterator = topJobStack.begin( );
		get_node_target = *iterator;
		if( get_node_target == nullptr )
			return false;
		topJobStack.erase( iterator );
	} while( true );
	return true;
}
