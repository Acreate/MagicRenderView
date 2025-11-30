#include "stringVectorInputPort.h"
#include <node/node/node.h>
bool StringVectorInputPort::init( Node *parent ) {

	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	return true;
}
