#include "floatInputPort.h"
#include <node/node/node.h>
bool FloatInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	return true;
}
