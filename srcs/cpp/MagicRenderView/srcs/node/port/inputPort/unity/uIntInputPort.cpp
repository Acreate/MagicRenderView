#include "uIntInputPort.h"

#include "../../../../director/varDirector.h"
bool UIntInputPort::init( Node *parent ) {
	if( UnityTypeInputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
