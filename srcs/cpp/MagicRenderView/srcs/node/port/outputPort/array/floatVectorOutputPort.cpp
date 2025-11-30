#include "floatVectorOutputPort.h"

#include <node/node/node.h>
bool FloatVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	return true;
}
