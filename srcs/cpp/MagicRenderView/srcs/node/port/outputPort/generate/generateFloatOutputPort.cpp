#include "generateFloatOutputPort.h"

#include "../../../../director/varDirector.h"
bool GenerateFloatOutputPort::init( Node *parent ) {

	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( double ), varTypeName ) == false )
		return false;
	return true;
}
