#include "anyVarTypeInputPort.h"

#include "../../../director/varDirector.h"
bool AnyVarTypeInputPort::init( Node *parent ) {
	if( InputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( void * ), varTypeName ) == false )
		return false;
	return true;
}
