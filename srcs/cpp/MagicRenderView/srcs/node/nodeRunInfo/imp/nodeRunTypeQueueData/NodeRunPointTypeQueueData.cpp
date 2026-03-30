#include "NodeRunPointTypeQueueData.h"

#include "../../../../enums/nodeEnum.h"
NodeRunPointTypeQueueData::NodeRunPointTypeQueueData( ) {
	setType( NodeEnum::NodeType::Point );
}
bool NodeRunPointTypeQueueData::appendNode( Node *append_node_ptr ) {
	return NodeRunTypeQueueData::appendNode( append_node_ptr );
}
bool NodeRunPointTypeQueueData::removeNode( const Node *remove_node_ptr ) {
	return NodeRunTypeQueueData::removeNode( remove_node_ptr );
}
const std::vector< Node * > & NodeRunPointTypeQueueData::getNodeQueue( ) const {
	return NodeRunTypeQueueData::getNodeQueue( );
}
NodeEnum::NodeType NodeRunPointTypeQueueData::getType( ) const {
	return NodeRunTypeQueueData::getType( );
}
