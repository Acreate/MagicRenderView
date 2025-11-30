#include "stringInputPort.h"

#include <node/node/node.h>
bool StringInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	return true;
}
