#include "nodeTools.h"

#include "arrayTools.h"
#include "vectorTools.h"

#include "../node/node/node.h"
bool NodeTools::getNodeRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
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
				if( ArrayTools::findIndex( resuktData, resultCount, appendData[ appendIndex ], findResult ) == true )
					topJobStack.emplace_front( appendData[ appendIndex ] );
			// 输入依赖
			auto &thisInRefNode = get_node_target->getOtherNodeOutputPortRefThisNodeInputPortVector( );
			appendCount = thisInRefNode.size( );
			appendData = thisInRefNode.data( );
			for( findResult = appendIndex = 0; appendIndex < appendCount; ++appendIndex, findResult = 0 )
				if( ArrayTools::findIndex( resuktData, resultCount, appendData[ appendIndex ], findResult ) == true )
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
bool NodeTools::getNodeInputInForRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	auto nodes = get_node_target->getOtherNodeOutputPortRefThisNodeInputPortVector( );
	size_t count = nodes.size( );
	auto data = nodes.data( );
	size_t index;
	size_t emplaceStartIndex = result_ref_node_vector.size( );
	size_t emplaceNewSize = emplaceStartIndex + count;
	size_t findIndex;
	result_ref_node_vector.resize( emplaceNewSize );
	size_t setIndex = emplaceStartIndex;
	auto emplaceData = result_ref_node_vector.data( );
	for( findIndex = 0, index = 0; index < count; ++index, findIndex = 0 )
		if( ArrayTools::findIndex( emplaceData, setIndex, data[ index ], findIndex ) == false ) {
			emplaceData[ setIndex ] = data[ index ];
			++setIndex;
		}
	result_ref_node_vector.resize( setIndex );
	for( index = 0; index < count; ++index )
		if( getNodeInputInForRef( data[ index ], result_ref_node_vector ) == false )
			return false;
	return true;
}
bool NodeTools::getNodeOutputInForRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	auto nodes = get_node_target->getThisNodeOutputPortRefOtherNodeInputPortVector( );
	size_t count = nodes.size( );
	auto data = nodes.data( );
	size_t index;
	size_t emplaceStartIndex = result_ref_node_vector.size( );
	size_t emplaceNewSize = emplaceStartIndex + count;
	size_t findIndex;
	result_ref_node_vector.resize( emplaceNewSize );
	size_t setIndex = emplaceStartIndex;
	auto emplaceData = result_ref_node_vector.data( );
	for( findIndex = 0, index = 0; index < count; ++index, findIndex = 0 )
		if( ArrayTools::findIndex( emplaceData, setIndex, data[ index ], findIndex ) == false ) {
			emplaceData[ setIndex ] = data[ index ];
			++setIndex;
		}
	result_ref_node_vector.resize( setIndex );
	for( index = 0; index < count; ++index )
		if( getNodeOutputInForRef( data[ index ], result_ref_node_vector ) == false )
			return false;
	return true;
}
