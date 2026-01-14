#include "imageVectorInputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool ImageVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QImage ), varTypeName ) == false )
		return false;
	return true;
}
