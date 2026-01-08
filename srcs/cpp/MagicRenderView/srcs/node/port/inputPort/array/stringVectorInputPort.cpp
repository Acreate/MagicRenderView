#include "stringVectorInputPort.h"
#include <node/node/node.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool StringVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QString ), varTypeName ) == false )
		return false;
	return true;
}
