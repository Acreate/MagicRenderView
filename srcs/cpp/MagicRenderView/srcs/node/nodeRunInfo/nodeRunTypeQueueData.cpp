#include "nodeRunTypeQueueData.h"

#include "../../tools/vectorTools.h"

#include "../node/node.h"
const std::vector< Node * > & NodeRunTypeQueueData::getNodeQueue( ) const { return nodeQueue; }
void NodeRunTypeQueueData::setNodeQueue( const std::vector< Node * > &node_queue ) { nodeQueue = node_queue; }
NodeEnum::NodeType NodeRunTypeQueueData::getType( ) const { return type; }
void NodeRunTypeQueueData::setType( NodeEnum::NodeType type ) { this->type = type; }
bool NodeRunTypeQueueData::appendNode( Node *append_node_ptr ) {
	if( append_node_ptr->getNodeType( ) != type )
		return false;
	size_t findeResult;
	if( VectorTools::findIndex( nodeQueue, append_node_ptr, findeResult ) == true )
		return true;
	nodeQueue.emplace_back( append_node_ptr );
	return true;
}
bool NodeRunTypeQueueData::removeNode( const Node *remove_node_ptr ) {
	size_t count = nodeQueue.size( );
	if( count == 0 )
		return false;
	auto nodeData = nodeQueue.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( nodeData[ index ] == remove_node_ptr ) {
			nodeQueue.erase( nodeQueue.begin( ) + index );
			return true;
		}
	return false;
}
NodeRunTypeQueueData::NodeRunTypeQueueData( ) { }
