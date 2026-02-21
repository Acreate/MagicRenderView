#include "nodeRunLink.h"

#include "../nodeRunLinkData.h"

#include "../../node/node.h"

NodeRunLink::~NodeRunLink( ) {
	delete nodeRunLinkData;
}
NodeRunLink::NodeRunLink( Node *const init_node_ptr ) {
	nodeRunLinkData = new NodeRunLinkData( init_node_ptr );
}
bool NodeRunLink::runRunNode( Node *run_node_ptr, const QDateTime &run_time, size_t run_frame ) {
	if( nodeRunLinkData->currentNode != run_node_ptr )
		return false;
	size_t count;
	Node **data;
	bool fillNodeCall = nodeRunLinkData->currentNode->fillNodeCall( run_time, run_frame );
	if( fillNodeCall == true ) {
		count = nodeRunLinkData->linkNodeVector.size( );
		data = nodeRunLinkData->linkNodeVector.data( );
		if( data[ count - 1 ] == run_node_ptr )
			nodeRunLinkData->over = true;
	}
	return fillNodeCall;
}
bool NodeRunLink::getNodeRunAdviseNodeVector( Node *get_advise_node_ptr, std::vector< Node * > &result_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) const {
	return nodeRunLinkData->getNodeRunAdviseNodeVector( get_advise_node_ptr, result_advise_node_vector, ndoe_run_start_data_time, current_frame );
}
bool NodeRunLink::adviseRunNode( const Node *const node ) const {
	return nodeRunLinkData->adviseRunNode( node );
}
const std::vector< Node * > & NodeRunLink::getAdviseNodeVector( ) const {
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
	return nodeRunLinkData->isReady( );
}
bool NodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return nodeRunLinkData->linkHasNode( check_node_ptr );
}
bool NodeRunLink::linkHasEndNode( const Node *const check_node_ptr ) const {
	return nodeRunLinkData->linkHasNode( check_node_ptr );
}
