#include "uIntCacheInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool UIntCacheInputPort::init( Node *parent ) {
	if( CacheTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
