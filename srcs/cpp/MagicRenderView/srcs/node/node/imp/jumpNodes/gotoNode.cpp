#include "gotoNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"

bool GotoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< InterFaceInputPort >( tr( "跳转" ) ) == nullptr )
			return false;

		return true;
	};
	return JumpNode::initEx( parent );
}
bool GotoNode::updateLayout( ) {
	if( JumpNode::updateLayout( ) == false )
		return false;
	return true;
}
