#include "generateColorOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool GenerateColorOutputPort::init( Node *parent ) {
	if( GenerateTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QColor ), varTypeName ) == false )
		return false;
	return true;
}
