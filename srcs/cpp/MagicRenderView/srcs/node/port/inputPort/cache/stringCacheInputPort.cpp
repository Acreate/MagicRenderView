#include "stringCacheInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool StringCacheInputPort::init( Node *parent ) {
	if( CacheTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QString ), varTypeName ) == false )
		return false;
	return true;
}
