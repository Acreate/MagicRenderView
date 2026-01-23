#include "colorVectorInputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool ColorVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QColor ), varTypeName ) == false )
		return false;
	return true;
}
