#include "generateFloatOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool GenerateFloatOutputPort::init( Node *parent ) {

	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( double ), varTypeName ) == false )
		return false;
	return true;
}
