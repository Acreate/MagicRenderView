#include "resultNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"

bool ResultNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< InterFaceInputPort >( tr( "过程结束" ) ) == nullptr )
			return false;
		return true;
	};
	return EndNode::initEx( parent );
}
bool ResultNode::updateLayout( ) {
	if( EndNode::updateLayout( ) == false )
		return false;
	return true;
}
