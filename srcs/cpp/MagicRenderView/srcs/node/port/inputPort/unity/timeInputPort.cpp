#include "timeInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
#include <QTime>
bool TimeInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QTime ), varTypeName ) == false )
		return false;
	return true;
}
