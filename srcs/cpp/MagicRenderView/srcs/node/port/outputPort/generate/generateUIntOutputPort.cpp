#include "generateUIntOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool GenerateUIntOutputPort::init( Node *parent ) {

	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
