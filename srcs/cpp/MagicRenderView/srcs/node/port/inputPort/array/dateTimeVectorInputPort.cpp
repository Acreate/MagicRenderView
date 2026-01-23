#include "dateTimeVectorInputPort.h"

#include <qdatetime.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool DateTimeVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QDateTime ), varTypeName ) == false )
		return false;
	return true;
}
