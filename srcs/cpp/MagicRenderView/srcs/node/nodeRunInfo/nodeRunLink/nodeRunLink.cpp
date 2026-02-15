#include "nodeRunLink.h"

#include "../../node/node.h"

NodeRunLink::~NodeRunLink( ) {
}
NodeRunLink::NodeRunLink( Node *const init_node_ptr ) : NodeRunLinkData( init_node_ptr ) {
}
bool NodeRunLink::runRunNode( Node *run_node_ptr, const QDateTime &run_time, size_t run_frame ) {
	if( currentNode != run_node_ptr )
		return false;
	return currentNode->fillNodeCall( run_time, run_frame );
}
