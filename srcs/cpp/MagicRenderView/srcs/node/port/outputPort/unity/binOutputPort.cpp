#include "binOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool BinOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint8_t ), varTypeName ) == false )
		return false;
	return true;
}
