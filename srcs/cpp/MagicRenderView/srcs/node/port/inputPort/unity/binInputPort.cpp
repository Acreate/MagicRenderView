#include "binInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool BinInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint8_t ), varTypeName ) == false )
		return false;
	return true;
}
