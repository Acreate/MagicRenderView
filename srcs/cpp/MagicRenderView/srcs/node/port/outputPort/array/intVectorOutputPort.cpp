#include "intVectorOutputPort.h"

#include <node/node/node.h>
bool IntVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	return true;
}
