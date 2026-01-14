#include "dateTimeOutputPort.h"

#include <qdatetime.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool DateTimeOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QDateTime ), varTypeName ) == false )
		return false;
	return true;
}
