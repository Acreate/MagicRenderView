#include "intInputPort.h"
#include <node/node/node.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool IntInputPort::init( Node *parent ) {

	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
