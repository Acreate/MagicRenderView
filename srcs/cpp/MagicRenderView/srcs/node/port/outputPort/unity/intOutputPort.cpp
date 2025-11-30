#include "intOutputPort.h"

#include <node/node/node.h>
bool IntOutputPort::init( Node *parent ) {

	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	return true;
}
