#include "uIntOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool UIntOutputPort::init( Node *parent ) {
	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
