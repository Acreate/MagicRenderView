#include "anyVarTypeOutputPort.h"

#include "../../../app/application.h"
#include "../../../director/varDirector.h"
bool AnyVarTypeOutputPort::init( Node *parent ) {
	if( OutputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( void * ), varTypeName ) == false )
		return false;
	return true;
}
