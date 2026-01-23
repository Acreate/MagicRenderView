#include "dateTimeInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
#include <qdatetime.h>
bool DateTimeInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QDateTime ), varTypeName ) == false )
		return false;
	return true;
}
