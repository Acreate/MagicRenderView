#include "uIntCacheOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool UIntCacheOutputPort::init( Node *parent ) {
	if( CacheTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( uint64_t ), varTypeName ) == false )
		return false;
	return true;
}
