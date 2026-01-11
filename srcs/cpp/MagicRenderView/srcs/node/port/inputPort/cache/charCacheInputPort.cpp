#include "charCacheInputPort.h"

#include <app/application.h>
#include <director/varDirector.h>
bool CharCacheInputPort::init( Node *parent ) {
	if( CacheTypeInputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QChar ), varTypeName ) == false )
		return false;
	return true;
}
