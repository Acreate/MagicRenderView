#include "anyOutputPort.h"
#include <node/node/node.h>
bool AnyOutputPort::init( Node *parent ) {

	if( AnyTypeOutputPort::init( parent ) == false )
		return false;
	return true;
}
