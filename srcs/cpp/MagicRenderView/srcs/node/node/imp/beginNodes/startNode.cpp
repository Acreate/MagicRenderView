#include "startNode.h"
#include "../../../port/outputPort/begin/beginOutputPort .h"
#include "../../../port/outputPort/toBegin/toBeginOutputPort.h"

bool StartNode::initEx( MainWidget *parent ) {

	initExCallFunction = [this] ( MainWidget *main_widget ) {
		auto beginOutputPort = appendOutputPortType< BeginOutputPort >( tr( "过程开始" ) );
		if( beginOutputPort == nullptr )
			return false;
		auto toBeginOutputPort = appendOutputPortType< ToBeginOutputPort >( tr( "过程返回" ) );
		if( toBeginOutputPort == nullptr )
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
