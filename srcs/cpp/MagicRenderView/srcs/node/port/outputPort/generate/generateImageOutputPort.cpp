#include "generateImageOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool GenerateImageOutputPort::init( Node *parent ) {
	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QImage ), varTypeName ) == false )
		return false;
	return true;
}
