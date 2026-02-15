#include "nodeRunLinkData.h"
NodeRunLinkData::NodeRunLinkData( Node *init_node_ptr ) {
	startNode = nullptr;
	currentNode = nullptr;
	beforeNode = init_node_ptr;
	over = false;
	ready = false;
}
bool NodeRunLinkData::isReady( ) const {
	return ready;
}
bool NodeRunLinkData::isOver( ) const {
	return over;
}
Node * NodeRunLinkData::getStartNode( ) const { return startNode; }
Node * NodeRunLinkData::getCurrentNode( ) const { return currentNode; }
Node * NodeRunLinkData::getBeforeNode( ) const { return beforeNode; }
