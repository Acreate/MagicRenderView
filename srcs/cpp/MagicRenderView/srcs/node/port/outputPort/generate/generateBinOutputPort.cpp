#include "generateBinOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool GenerateBinOutputPort::init( Node *parent ) {
	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint8_t ), varTypeName ) == false )
		return false;
	return true;
}
