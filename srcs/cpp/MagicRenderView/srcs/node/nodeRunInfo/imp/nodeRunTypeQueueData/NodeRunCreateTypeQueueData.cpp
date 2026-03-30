#include "NodeRunCreateTypeQueueData.h"

#include "../../../../enums/nodeEnum.h"
NodeRunCreateTypeQueueData::NodeRunCreateTypeQueueData( ) {
	setType( NodeEnum::NodeType::Create );
}
bool NodeRunCreateTypeQueueData::appendNode( Node *append_node_ptr ) {
	return NodeRunTypeQueueData::appendNode( append_node_ptr );
}
bool NodeRunCreateTypeQueueData::removeNode( const Node *remove_node_ptr ) {
	return NodeRunTypeQueueData::removeNode( remove_node_ptr );
}
const std::vector< Node * > & NodeRunCreateTypeQueueData::getNodeQueue( ) const {
	return NodeRunTypeQueueData::getNodeQueue( );
}
NodeEnum::NodeType NodeRunCreateTypeQueueData::getType( ) const {
	return NodeRunTypeQueueData::getType( );
}
