#include "anyVarTypeInputPort.h"

#include "../../../app/application.h"
#include "../../../director/varDirector.h"
bool AnyVarTypeInputPort::init( Node *parent ) {
	if( InputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( void * ), varTypeName ) == false )
		return false;
	return true;
}
