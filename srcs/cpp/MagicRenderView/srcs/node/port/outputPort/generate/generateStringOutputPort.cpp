#include "generateStringOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool GenerateStringOutputPort::init( Node *parent ) {

	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QString ), varTypeName ) == false )
		return false;
	return true;
}
