#include "floatVectorOutputPort.h"

#include <node/node/node.h>

#include "../../../../director/varDirector.h"
bool FloatVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( double ), varTypeName ) == false )
		return false;
	return true;
}
