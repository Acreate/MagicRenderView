#include "dateInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
#include <QDate>
bool DateInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QDate ), varTypeName ) == false )
		return false;
	return true;
}
