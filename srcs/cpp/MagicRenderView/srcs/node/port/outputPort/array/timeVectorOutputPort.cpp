#include "timeVectorOutputPort.h"

#include <QTime>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool TimeVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QTime ), varTypeName ) == false )
		return false;
	return true;
}
