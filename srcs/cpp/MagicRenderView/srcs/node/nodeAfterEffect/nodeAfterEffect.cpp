#include "nodeAfterEffect.h"
NodeEnum::NodeSelctType NodeAfterEffect::getNodeSelctType( ) const { return nodeSelctType; }
void NodeAfterEffect::setNodeSelctType( NodeEnum::NodeSelctType node_selct_type ) {
	nodeSelctType = node_selct_type;
	update( );
}
NodeEnum::NodeStatusType NodeAfterEffect::getNodeStatusType( ) const { return nodeStatusType; }
void NodeAfterEffect::setNodeStatusType( NodeEnum::NodeStatusType node_status_type ) {
	nodeStatusType = node_status_type;
	update( );
}
