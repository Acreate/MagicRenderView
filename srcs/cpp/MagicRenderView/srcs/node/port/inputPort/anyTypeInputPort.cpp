#include "anyTypeInputPort.h"
AnyTypeInputPort::AnyTypeInputPort( const QString &name ) : InputPort( name ) {
	varTypeName = tr( "所有" );
	varPtr = nullptr;
}
