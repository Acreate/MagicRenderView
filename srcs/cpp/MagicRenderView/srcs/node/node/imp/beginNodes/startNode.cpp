#include "startNode.h"

#include "../../../port/outputPort/interface/interFaceOutputPort.h"

bool StartNode::init( DrawNodeWidget *parent ) {
	if( BeginNode::init( parent ) == false )
		return false;
	if( appendOutputPortType< InterFaceOutputPort >( tr( "过程开始" ) ) == nullptr )
		return false;
	return true;
}
bool StartNode::updateLayout( ) {
	if( BeginNode::updateLayout( ) == false )
		return false;
	return true;
}
