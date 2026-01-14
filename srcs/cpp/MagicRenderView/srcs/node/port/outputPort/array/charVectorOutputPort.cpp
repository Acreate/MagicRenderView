#include "charVectorOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool CharVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QChar ), varTypeName ) == false )
		return false;
	return true;
}
