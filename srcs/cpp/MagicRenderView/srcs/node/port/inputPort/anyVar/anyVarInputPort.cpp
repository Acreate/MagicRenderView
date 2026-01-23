#include "anyVarInputPort.h"

#include "../../../../director/varDirector.h"
bool AnyVarInputPort::init( Node *parent ) {
	if( AnyVarTypeInputPort::init( parent ) == false )
		return false;
	return true;
}
