#include "intInputPort.h"
#include <node/node/node.h>
bool IntInputPort::init( Node *parent ) {

	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	return true;
}
