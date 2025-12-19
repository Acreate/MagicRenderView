#include "uIntVectorOutputPort.h"

#include "../../../../director/varDirector.h"
bool UIntVectorOutputPort::init( Node *parent ) {
	if( ArrayTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
