#include "dateVectorInputPort.h"

#include <QDate>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool DateVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QDate ), varTypeName ) == false )
		return false;
	return true;
}
