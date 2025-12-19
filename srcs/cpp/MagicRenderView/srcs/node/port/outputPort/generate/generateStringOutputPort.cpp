#include "generateStringOutputPort.h"

#include "../../../../director/varDirector.h"
bool GenerateStringOutputPort::init( Node *parent ) {

	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( QString ), varTypeName ) == false )
		return false;
	return true;
}
