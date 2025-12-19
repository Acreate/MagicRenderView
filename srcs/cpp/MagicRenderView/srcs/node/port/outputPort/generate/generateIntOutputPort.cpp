#include "generateIntOutputPort.h"

#include "../../../../director/varDirector.h"
bool GenerateIntOutputPort::init( Node *parent ) {

	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
