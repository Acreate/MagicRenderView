#include "resultNode.h"

#include "../../../port/inputPort/any/anyInputPort.h"

bool ResultNode::init( DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info ) {
	if( EndNode::init( parent, node_ref_link_info ) == false )
		return false;
	if( appendInputPortType< AnyInputPort >( tr( "过程结束" ) ) == nullptr )
		return false;
	return true;
}
bool ResultNode::updateLayout( ) {
	if( EndNode::updateLayout( ) == false )
		return false;
	return true;
}
