#include "imageVectorOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool ImageVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QImage ), varTypeName ) == false )
		return false;
	return true;
}
