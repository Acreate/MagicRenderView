#include "stringVectorOutputPort.h"

#include <node/node/node.h>

#include "../../../../director/varDirector.h"
bool StringVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( QString ), varTypeName ) == false )
		return false;
	return true;
}
