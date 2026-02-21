#include "callNodeRunLink.h"
bool CallNodeRunLink::builder( ) {
	return false;
}
bool CallNodeRunLink::getNextRunNode( const std::vector< Node * > &over_run_node_vector, Node *&result_next_node_ptr ) {
	if( isOver( ) )
		return false;
	return true;
}
