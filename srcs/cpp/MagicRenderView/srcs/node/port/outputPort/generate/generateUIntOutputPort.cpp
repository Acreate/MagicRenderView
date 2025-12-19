#include "generateUIntOutputPort.h"

#include "../../../../director/varDirector.h"
bool GenerateUIntOutputPort::init( Node *parent ) {

	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
