#include "floatVectorInputPort.h"
#include <node/node/node.h>
bool FloatVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	return true;
}
