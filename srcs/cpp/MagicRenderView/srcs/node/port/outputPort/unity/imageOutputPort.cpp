#include "imageOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool ImageOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QImage ), varTypeName ) == false )
		return false;
	return true;
}
