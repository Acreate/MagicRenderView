#include "qColorInputPort.h"

#include <qt/varType/I_Type.h>

#include <qt/varType/I_Var.h>

Imp_StaticMetaInfo( QColorInputPort, QObject::tr( "qcolor" ), QObject::tr( "inputPort" ) );
QColorInputPort::QColorInputPort( NodeItem *parent ) : NodeInputPort( parent ) {
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
