#include "nodeRunLink.h"

#include "../nodeRunLinkData.h"

#include "../../../tools/NodeRunLinkTools.h"
#include "../../../tools/arrayTools.h"

#include "../../node/node.h"

NodeRunLink::~NodeRunLink( ) {
	delete get;
	delete nodeRunLinkData;
}
NodeRunLink::NodeRunLink( Node *const init_node_ptr ) {
	nodeRunLinkData = new NodeRunLinkData( init_node_ptr );
	get = new NodeRunLinkTools::Get( nodeRunLinkData );
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
	return nodeRunLinkData->ready;
}
bool NodeRunLink::linkHasNode( const Node *const check_node_ptr ) const {
	return nodeRunLinkData->linkHasNode( check_node_ptr );
}
bool NodeRunLink::linkHasEndNode( const Node *const check_node_ptr ) const {
	return nodeRunLinkData->linkHasNode( check_node_ptr );
}
bool NodeRunLink::sortBilderList( const std::vector< Node * > &reference_sort_vector ) {
	size_t startCount = nodeRunLinkData->linkNodeVector.size( );
	if( startCount == 0 )
		return false;
	size_t refCount = reference_sort_vector.size( );
	if( refCount == 0 )
		return false;
	auto sortData = nodeRunLinkData->linkNodeVector.data( );

	std::vector< Node * > *buff;
	buff = new std::vector< Node * >( startCount );
	auto refData = reference_sort_vector.data( );

	auto buffData = buff->data( );
	size_t buffIndex = 0;

	size_t startIndex;
	size_t refIndex;

	for( startIndex = 0, refIndex = 0; refIndex < refCount; ++refIndex, startIndex = 0 )
		if( ArrayTools::findIndex( sortData, startCount, refData[ refIndex ], startIndex ) == true ) {
			if( buffIndex == startCount ) {
				delete buff;
				return false;
			}
			buffData[ buffIndex ] = refData[ refIndex ];
			++buffIndex;
		}
	for( refIndex = 0; refIndex < startCount; ++refIndex )
		sortData[ refIndex ] = buffData[ refIndex ];
	delete buff;
	return true;
}
