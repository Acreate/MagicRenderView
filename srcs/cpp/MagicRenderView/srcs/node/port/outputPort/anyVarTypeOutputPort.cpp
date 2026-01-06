#include "anyVarTypeOutputPort.h"

#include "../../../director/varDirector.h"
bool AnyVarTypeOutputPort::init( Node *parent ) {
	if( OutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( void * ), varTypeName ) == false )
		return false;
	return true;
}
