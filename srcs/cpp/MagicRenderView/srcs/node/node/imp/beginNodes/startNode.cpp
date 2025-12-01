#include "startNode.h"

#include "../../../port/outputPort/any/anyOutputPort.h"

bool StartNode::init( DrawNodeWidget *parent ) {
	bool init = BeginNode::init( parent );
	if( init == false )
		return init;
	if( appendOutputPortType< AnyOutputPort >( tr( "过程开始" ) ) == nullptr )
		return false;
	return init;
}
bool StartNode::updateLayout( ) {
	if( BeginNode::updateLayout( ) == false )
		return false;
	return true;
}
