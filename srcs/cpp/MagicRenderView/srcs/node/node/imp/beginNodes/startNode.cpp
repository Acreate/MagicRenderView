#include "startNode.h"

#include "../../../port/outputPort/begin/beginOutputPort .h"
#include "../../../port/outputPort/toBegin/toBeginOutputPort.h"

bool StartNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendOutputPortType< BeginOutputPort >( tr( "过程开始" ) ) == nullptr )
			return false;
		if( appendOutputPortType< ToBeginOutputPort >( tr( "过程返回" ) ) == nullptr )
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
