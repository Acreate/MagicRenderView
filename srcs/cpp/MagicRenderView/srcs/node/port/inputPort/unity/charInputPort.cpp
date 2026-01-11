#include "charInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool CharInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QChar ), varTypeName ) == false )
		return false;
	return true;
}
