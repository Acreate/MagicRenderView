#include "dateTimeVectorOutputPort.h"

#include <QDateTime>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool DateTimeVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QDateTime ), varTypeName ) == false )
		return false;
	return true;
}
