#include "stringVectorInputPort.h"
#include <node/node/node.h>

#include "../../../../director/varDirector.h"
bool StringVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( QString ), varTypeName ) == false )
		return false;
	return true;
}
