#include "floatOutputPort.h"

#include <node/node/node.h>
bool FloatOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	return true;
}
