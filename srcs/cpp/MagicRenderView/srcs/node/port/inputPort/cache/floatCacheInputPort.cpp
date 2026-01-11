#include "floatCacheInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool FloatCacheInputPort::init( Node *parent ) {
	if( CacheTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( double ), varTypeName ) == false )
		return false;
	return true;
}
