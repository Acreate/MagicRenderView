#include "colorCacheOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool ColorCacheOutputPort::init( Node *parent ) {
	if( CacheTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QColor ), varTypeName ) == false )
		return false;
	return true;
}
