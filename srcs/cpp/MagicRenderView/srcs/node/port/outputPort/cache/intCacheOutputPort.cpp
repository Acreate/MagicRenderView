#include "intCacheOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool IntCacheOutputPort::init( Node *parent ) {
	if( CacheTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
