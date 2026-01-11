#include "imageCacheOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool ImageCacheOutputPort::init( Node *parent ) {
	if( CacheTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QImage ), varTypeName ) == false )
		return false;
	return true;
}
