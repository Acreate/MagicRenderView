#include "uIntVectorInputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool UIntVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
