#include "intOutputPort.h"

#include <node/node/node.h>

#include "../../../../director/varDirector.h"
IntOutputPort::IntOutputPort( const QString &name ) : UnityTypeOutputPort( name ) {

}
bool IntOutputPort::init( Node *parent ) {

	if( UnityTypeOutputPort::init( parent ) == false )
		return false;
	if( varDirector->getTypeName( typeid( int64_t ), varTypeName ) == false )
		return false;
	return true;
}
