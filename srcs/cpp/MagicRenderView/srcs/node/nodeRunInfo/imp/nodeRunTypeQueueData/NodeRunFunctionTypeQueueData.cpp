#include "NodeRunFunctionTypeQueueData.h"

#include "../../../../enums/nodeEnum.h"
NodeRunFunctionTypeQueueData::NodeRunFunctionTypeQueueData( ) {
	setType( NodeEnum::NodeType::Function );
}
bool NodeRunFunctionTypeQueueData::appendNode( Node *append_node_ptr ) {
	return NodeRunTypeQueueData::appendNode( append_node_ptr );
}
bool NodeRunFunctionTypeQueueData::removeNode( const Node *remove_node_ptr ) {
	return NodeRunTypeQueueData::removeNode( remove_node_ptr );
}
const std::vector< Node * > & NodeRunFunctionTypeQueueData::getNodeQueue( ) const {
	return NodeRunTypeQueueData::getNodeQueue( );
}
NodeEnum::NodeType NodeRunFunctionTypeQueueData::getType( ) const {
	return NodeRunTypeQueueData::getType( );
}
