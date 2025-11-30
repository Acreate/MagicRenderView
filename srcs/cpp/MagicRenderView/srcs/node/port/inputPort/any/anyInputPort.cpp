#include "anyInputPort.h"

#include <node/node/node.h>
bool AnyInputPort::init( Node *parent ) {
	if( AnyTypeInputPort::init( parent ) == false )
		return false;
	return true;
}
