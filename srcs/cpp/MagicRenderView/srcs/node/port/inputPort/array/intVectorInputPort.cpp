#include "intVectorInputPort.h"
#include <node/node/node.h>
bool IntVectorInputPort::init( Node *parent ) {

	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	return true;
}
