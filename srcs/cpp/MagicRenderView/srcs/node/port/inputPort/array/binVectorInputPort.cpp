#include "binVectorInputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool BinVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint8_t ), varTypeName ) == false )
		return false;
	return true;
}
