#include "nodeTools.h"
bool NodeTools::getNodeRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	return false;
}
bool NodeTools::getNodeInputRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	return false;
}
bool NodeTools::getNodeOutputRef( Node *get_node_target, std::vector< Node * > &result_ref_node_vector ) {
	return false;
}
std::vector< Node * > NodeTools::filterNodeVector( const std::vector< Node * > &src_vector, const std::vector< Node * > &target_vector ) {
	std::vector< Node * > result;
	size_t count = target_vector.size( );
	auto data = target_vector.data( );
	size_t index;
	for( auto &item : src_vector ) {
		for( index = 0; index < count; ++index )
			if( item == data[ index ] )
				break;
		if( index != count )
			continue;
		result.emplace_back( item );
	}
	return result;
}
