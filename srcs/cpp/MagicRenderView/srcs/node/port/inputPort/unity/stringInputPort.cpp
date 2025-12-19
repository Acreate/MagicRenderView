#include "stringInputPort.h"

#include <node/node/node.h>

#include "../../../../director/varDirector.h"
bool StringInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( QString ), varTypeName ) == false )
		return false;
	return true;
}
