#include "startNode.h"

#include "../../../port/outputPort/any/anyOutputPort.h"

bool StartNode::init( DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info ) {
	bool init = BeginNode::init( parent, node_ref_link_info );
	if( init == false )
		return init;
	if( appendOutputPortType< AnyOutputPort >( tr( "开始" ) ) == nullptr )
		return false;
	return init;
}
bool StartNode::updateLayout( ) {
	if( BeginNode::updateLayout( ) == false )
		return false;
	return true;
}
