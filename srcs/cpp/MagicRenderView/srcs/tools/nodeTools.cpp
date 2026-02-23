#include "nodeTools.h"

#include "arrayTools.h"

#include "../node/node/node.h"
bool NodeTools::getNodeRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	return false;
}
bool NodeTools::getNodeInputRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
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
			emplaceData[ emplaceStartIndex ] = data[ index ];
			++setIndex;
		}
	result_ref_node_vector.resize( setIndex );
	for( index = 0; index < count; ++index )
		if( getNodeInputRef( data[ index ], result_ref_node_vector ) == false )
			return false;
	return true;
}
bool NodeTools::getNodeOutputRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
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
			emplaceData[ emplaceStartIndex ] = data[ index ];
			++setIndex;
		}
	result_ref_node_vector.resize( setIndex );
	for( index = 0; index < count; ++index )
		if( getNodeOutputRef( data[ index ], result_ref_node_vector ) == false )
			return false;
	return true;
}
