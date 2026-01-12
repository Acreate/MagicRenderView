#include "dateVectorOutputPort.h"

#include <QDate>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool DateVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QDate ), varTypeName ) == false )
		return false;
	return true;
}
