#include "nodeAfterEffect.h"
NodeEnum::NodeSelctType NodeAfterEffect::getNodeSelctType( ) const { return nodeSelctType; }
void NodeAfterEffect::setNodeSelctType( NodeEnum::NodeSelctType node_selct_type ) {
	if( node_selct_type == nodeSelctType )
		return;
	nodeSelctType = node_selct_type;
	update( );
}
NodeEnum::NodeStatusType NodeAfterEffect::getNodeStatusType( ) const { return nodeStatusType; }
void NodeAfterEffect::setNodeStatusType( NodeEnum::NodeStatusType node_status_type ) {
	if( node_status_type == nodeStatusType )
		return;
	nodeStatusType = node_status_type;
	update( );
}
