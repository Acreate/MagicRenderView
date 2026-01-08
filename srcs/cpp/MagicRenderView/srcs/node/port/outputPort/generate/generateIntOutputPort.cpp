#include "generateIntOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool GenerateIntOutputPort::init( Node *parent ) {

	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
