#include "boolVectorOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool BoolVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( bool ), varTypeName ) == false )
		return false;
	return true;
}
