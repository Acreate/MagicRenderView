#include "gotoNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"
#include "../../../port/inputPort/point/pointInputPort.h"
#include "../../../port/inputPort/toPoint/toPointInputPort.h"

bool GotoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< PointInputPort >( tr( "跳转" ) ) == nullptr )
			return false;
		if( appendInputPortType< ToPointInputPort >( tr( "跳到定点" ) ) == nullptr )
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
