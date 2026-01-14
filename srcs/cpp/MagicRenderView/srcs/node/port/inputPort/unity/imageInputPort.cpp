#include "imageInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool ImageInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QImage ), varTypeName ) == false )
		return false;
	return true;
}
