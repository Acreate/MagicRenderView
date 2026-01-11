#include "imageCacheInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool ImageCacheInputPort::init( Node *parent ) {
	if( CacheTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QImage ), varTypeName ) == false )
		return false;
	return true;
}
