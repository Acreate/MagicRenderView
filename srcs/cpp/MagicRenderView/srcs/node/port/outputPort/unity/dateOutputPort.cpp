#include "dateOutputPort.h"

#include <QDate>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool DateOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QDate ), varTypeName ) == false )
		return false;
	return true;
}
