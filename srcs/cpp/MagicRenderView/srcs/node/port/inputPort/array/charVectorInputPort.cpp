#include "charVectorInputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool CharVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QChar ), varTypeName ) == false )
		return false;
	return true;
}
