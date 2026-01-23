#include "boolOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool BoolOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( bool ), varTypeName ) == false )
		return false;
	return true;
}
