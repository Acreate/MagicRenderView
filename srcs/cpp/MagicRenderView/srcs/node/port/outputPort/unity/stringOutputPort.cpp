#include "stringOutputPort.h"

#include <node/node/node.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool StringOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QString ), varTypeName ) == false )
		return false;
	return true;
}
