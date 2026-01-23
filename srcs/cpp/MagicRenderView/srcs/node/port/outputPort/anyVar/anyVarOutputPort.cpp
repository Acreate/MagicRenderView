#include "anyVarOutputPort.h"

#include "../../../../director/varDirector.h"
bool AnyVarOutputPort::init( Node *parent ) {
	if( AnyVarTypeOutputPort::init( parent ) == false )
		return false;
	return true;
}
