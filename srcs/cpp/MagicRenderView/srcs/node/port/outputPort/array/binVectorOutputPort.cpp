#include "binVectorOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool BinVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint8_t ), varTypeName ) == false )
		return false;
	return true;
}
