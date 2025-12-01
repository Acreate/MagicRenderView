#include "anyTypeOutputPort.h"
AnyTypeOutputPort::AnyTypeOutputPort( const QString &name ) : OutputPort( name ) {
	varTypeName = tr( "所有" );
	varPtr = nullptr;
}
