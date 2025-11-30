#include "stringOutputPort.h"

#include <node/node/node.h>
bool StringOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	return true;
}
