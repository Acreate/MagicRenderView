#include "floatInputPort.h"
#include <node/node/node.h>

#include "../../../../director/varDirector.h"
bool FloatInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( double ), varTypeName ) == false )
		return false;
	return true;
}
