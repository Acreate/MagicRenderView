#include "gotoNode.h"

#include "../../../port/inputPort/any/anyInputPort.h"
#include "../../../port/inputPort/jump/jumpInputPort.h"
#include "../../../port/outputPort/any/anyOutputPort.h"

bool GotoNode::updateLayout( ) {
	if( JumpNode::updateLayout( ) == false )
		return false;
	return true;
}
bool GotoNode::init( DrawNodeWidget *parent ) {
	if( JumpNode::init( parent ) == false )
		return false;
	if( appendInputPortType< JumpInputPort >( tr( "过程接入" ) ) == nullptr )
		return false;

	return true;
}
