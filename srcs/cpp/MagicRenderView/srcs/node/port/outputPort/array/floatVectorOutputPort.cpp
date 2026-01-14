#include "floatVectorOutputPort.h"

#include <node/node/node.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool FloatVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( double ), varTypeName ) == false )
		return false;
	return true;
}
