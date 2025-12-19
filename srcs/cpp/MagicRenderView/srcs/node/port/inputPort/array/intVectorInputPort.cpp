#include "intVectorInputPort.h"
#include <node/node/node.h>

#include "../../../../director/varDirector.h"
bool IntVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
