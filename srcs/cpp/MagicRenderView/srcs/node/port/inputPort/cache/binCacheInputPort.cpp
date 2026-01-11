#include "binCacheInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool BinCacheInputPort::init( Node *parent ) {
	if( CacheTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint8_t * ), varTypeName ) == false )
		return false;
	return true;
}
