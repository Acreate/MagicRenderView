#include "intOutputPort.h"

#include <node/node/node.h>

#include "../../../../app/application.h"
#include "../../../../director/varDirector.h"
IntOutputPort::IntOutputPort( const QString &name ) : UnityTypeOutputPort( name ) {

}
bool IntOutputPort::init( Node *parent ) {

	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
