#include "stringVectorOutputPort.h"

#include <node/node/node.h>
bool StringVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	return true;
}
