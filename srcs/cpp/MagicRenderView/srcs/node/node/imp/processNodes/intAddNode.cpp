#include "intAddNode.h"

#include "../../../port/inputPort/unity/intInputPort.h"
#include "../../../port/outputPort/unity/intOutputPort.h"
bool IntAddNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntAddNode::init( DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info ) {
	if( ProcessNode::init( parent, node_ref_link_info ) == false )
		return false;
	if( appendInputPortType< IntInputPort >( tr( "被加数" ) ) == nullptr )
		return false;
	if( appendInputPortType< IntInputPort >( tr( "加数" ) ) == nullptr )
		return false;
	if( appendOutputPortType< IntOutputPort >( tr( "和" ) ) == nullptr )
		return false;
	return true;
}
