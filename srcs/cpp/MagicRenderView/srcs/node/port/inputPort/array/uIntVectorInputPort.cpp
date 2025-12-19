#include "uIntVectorInputPort.h"

#include "../../../../director/varDirector.h"
bool UIntVectorInputPort::init( Node *parent ) {
	if( ArrayTypeInputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
