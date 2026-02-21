#include "nodeRunLink.h"

#include "../../node/node.h"

NodeRunLink::~NodeRunLink( ) {
}
NodeRunLink::NodeRunLink( Node *const init_node_ptr ) : NodeRunLinkData( init_node_ptr ) {
}
bool NodeRunLink::runRunNode( Node *run_node_ptr, const QDateTime &run_time, size_t run_frame ) {
	if( currentNode != run_node_ptr )
		return false;
	size_t count;
	Node **data;
	bool fillNodeCall = currentNode->fillNodeCall( run_time, run_frame );
	if( fillNodeCall == true ) {
		count = linkNodeVector.size( );
		data = linkNodeVector.data( );
		if( data[ count - 1 ] == run_node_ptr )
			over = true;
	}
	return fillNodeCall;
}
bool NodeRunLink::adviseRunNode( const Node *const node ) const {
	return NodeRunLinkData::adviseRunNode( node );
}
const std::vector< Node * > & NodeRunLink::getAdviseNodeVector( ) const {
	return NodeRunLinkData::getAdviseNodeVector( );
}
Node * NodeRunLink::getBeforeNode( ) const {
	return NodeRunLinkData::getBeforeNode( );
}
Node * NodeRunLink::getCurrentNode( ) const {
	return NodeRunLinkData::getCurrentNode( );
}
const std::vector< Node * > & NodeRunLink::getLinkNodeVector( ) const {
	return NodeRunLinkData::getLinkNodeVector( );
}
const std::vector< Node * > & NodeRunLink::getOverRunNodeVector( ) const {
	return NodeRunLinkData::getOverRunNodeVector( );
}
const std::vector< Node * > & NodeRunLink::getStartNodeVector( ) const {
	return NodeRunLinkData::getStartNodeVector( );
}
bool NodeRunLink::linkHasStartNode( const Node *const check_start_node_ptr ) const {
	return NodeRunLinkData::linkHasStartNode( check_start_node_ptr );
}
bool NodeRunLink::isOver( ) const {
	return NodeRunLinkData::isOver( );
}
bool NodeRunLink::isReady( ) const {
	return NodeRunLinkData::isReady( );
}
bool NodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return NodeRunLinkData::linkHasNode( check_node_ptr );
}
bool NodeRunLink::linkHasEndNode( const Node *const check_node_ptr ) const {
	return NodeRunLinkData::linkHasNode( check_node_ptr );
}
