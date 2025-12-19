#include "floatOutputPort.h"

#include <node/node/node.h>

#include "../../../../director/varDirector.h"
bool FloatOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( double ), varTypeName ) == false )
		return false;
	return true;
}
