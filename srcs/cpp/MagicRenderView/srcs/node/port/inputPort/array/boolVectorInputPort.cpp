#include "boolVectorInputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool BoolVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( bool ), varTypeName ) == false )
		return false;
	return true;
}
