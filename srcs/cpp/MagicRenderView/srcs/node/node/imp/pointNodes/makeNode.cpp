#include "makeNode.h"

#include "../../../port/inputPort/any/anyInputPort.h"
#include "../../../port/outputPort/any/anyOutputPort.h"

bool MakeNode::updateLayout( ) {
	if( PointNode::updateLayout( ) == false )
		return false;
	return true;
}
bool MakeNode::init( DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info ) {
	if( PointNode::init( parent, node_ref_link_info ) == false )
		return false;
	if( appendInputPortType< AnyInputPort >( tr( "过程接入" ) ) == nullptr )
		return false;
	if( appendOutputPortType< AnyOutputPort >( tr( "过程转移" ) ) == nullptr )
		return false;
	return true;
}
