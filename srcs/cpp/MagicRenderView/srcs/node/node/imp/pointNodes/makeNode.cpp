#include "makeNode.h"

#include "../../../port/inputPort/any/anyInputPort.h"
#include "../../../port/inputPort/point/pointInputPort.h"
#include "../../../port/outputPort/any/anyOutputPort.h"
#include "../../../port/outputPort/point/pointOutputPort.h"

bool MakeNode::updateLayout( ) {
	if( PointNode::updateLayout( ) == false )
		return false;
	return true;
}
bool MakeNode::init( DrawNodeWidget *parent ) {
	if( PointNode::init( parent ) == false )
		return false;
	if( appendOutputPortType< PointOutputPort >( tr( "过程转移" ) ) == nullptr )
		return false;
	return true;
}
