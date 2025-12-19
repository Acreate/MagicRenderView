#include "gotoNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"

bool GotoNode::updateLayout( ) {
	if( JumpNode::updateLayout( ) == false )
		return false;
	return true;
}
bool GotoNode::init( DrawNodeWidget *parent ) {
	if( JumpNode::init( parent ) == false )
		return false;
	if( appendInputPortType< InterFaceInputPort >( tr( "跳转" ) ) == nullptr )
		return false;

	return true;
}
