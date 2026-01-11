#include "intCacheInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool IntCacheInputPort::init( Node *parent ) {
	if( CacheTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
