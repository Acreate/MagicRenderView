#include "charCacheOutputPort.h"

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
bool CharCacheOutputPort::init( Node *parent ) {
	if( CacheTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( QChar ), varTypeName ) == false )
		return false;
	return true;
}
