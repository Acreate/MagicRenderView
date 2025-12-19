#include "makeNode.h"

#include "../../../port/outputPort/interface/interFaceOutputPort.h"

bool MakeNode::updateLayout( ) {
	if( PointNode::updateLayout( ) == false )
		return false;
	return true;
}
bool MakeNode::init( DrawNodeWidget *parent ) {
	if( PointNode::init( parent ) == false )
		return false;
	if( appendOutputPortType< InterFaceOutputPort >( tr( "过程转移" ) ) == nullptr )
		return false;
	return true;
}
