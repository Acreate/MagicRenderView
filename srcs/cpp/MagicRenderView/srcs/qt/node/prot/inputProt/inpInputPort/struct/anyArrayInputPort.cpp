#include "anyArrayInputPort.h"
#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>

#include <qt/appType/any.h>

Imp_StaticMetaInfo( AnyArrayInputPort, QObject::tr( "anyArray" ), QObject::tr( "inputPort" ) );
AnyArrayInputPort::AnyArrayInputPort( NodeItem *parent ) : NodeInputPort( parent ) {
	auto typePtr = new I_Type(
		typeid( t_current_type ),
		sizeof( t_current_type ),
		[] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		},
		[]( ) ->void * {
			return new t_current_type( );
		} );
	varPtr.reset( new I_Var( typePtr, title ) );
	setTitle( getMetaObjectName( ) );
}
