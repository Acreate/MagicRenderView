#include "timeOutputPort.h"

#include <QTime>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool TimeOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QTime ), varTypeName ) == false )
		return false;
	return true;
}
