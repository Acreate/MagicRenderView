#include "charOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool CharOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QChar ), varTypeName ) == false )
		return false;
	return true;
}
