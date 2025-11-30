#include "gotoNode.h"

#include "../../../port/inputPort/any/anyInputPort.h"
#include "../../../port/outputPort/any/anyOutputPort.h"

bool GotoNode::updateLayout( ) {
	if( JumpNode::updateLayout( ) == false )
		return false;
	return true;
}
bool GotoNode::init( DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info ) {
	if( JumpNode::init( parent, node_ref_link_info ) == false )
		return false;
	if( appendInputPortType< AnyInputPort >( tr( "过程接入" ) ) == nullptr )
		return false;

	return true;
}
