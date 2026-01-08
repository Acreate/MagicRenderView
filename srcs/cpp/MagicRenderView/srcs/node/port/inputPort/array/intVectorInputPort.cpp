#include "intVectorInputPort.h"
#include <node/node/node.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool IntVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
