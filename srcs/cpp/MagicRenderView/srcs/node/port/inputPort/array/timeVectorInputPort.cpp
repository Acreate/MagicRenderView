#include "timeVectorInputPort.h"

#include <QTime>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool TimeVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QTime ), varTypeName ) == false )
		return false;
	return true;
}
