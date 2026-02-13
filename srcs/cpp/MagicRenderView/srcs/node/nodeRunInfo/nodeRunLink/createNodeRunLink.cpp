#include "createNodeRunLink.h"
CreateNodeRunLink::CreateNodeRunLink( Node *const init_node_ptr ) : NodeRunLink( init_node_ptr ) { }

bool CreateNodeRunLink::builder( ) {
	return false;
}

bool CreateNodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return false;
}
bool CreateNodeRunLink::getNextRunNode( Node *&result_next_node_ptr ) {
	return false;
}
bool CreateNodeRunLink::getCurrentRunNode( Node *&result_current_node_ptr ) {
	return false;
}
