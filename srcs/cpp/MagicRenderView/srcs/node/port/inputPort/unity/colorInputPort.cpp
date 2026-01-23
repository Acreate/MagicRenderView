#include "colorInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool ColorInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QColor ), varTypeName ) == false )
		return false;
	return true;
}
