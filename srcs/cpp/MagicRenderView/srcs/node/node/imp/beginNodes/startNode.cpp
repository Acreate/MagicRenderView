#include "startNode.h"

#include "../../../port/outputPort/interface/interFaceOutputPort.h"

bool StartNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendOutputPortType< InterFaceOutputPort >( tr( "过程开始" ) ) == nullptr )
			return false;
		return true;
	};
	return BeginNode::initEx( parent );
}

bool StartNode::updateLayout( ) {
	if( BeginNode::updateLayout( ) == false )
		return false;
	return true;
}
