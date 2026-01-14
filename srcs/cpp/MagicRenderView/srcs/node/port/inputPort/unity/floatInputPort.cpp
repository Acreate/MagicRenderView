#include "floatInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool FloatInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( double ), varTypeName ) == false )
		return false;
	return true;
}
