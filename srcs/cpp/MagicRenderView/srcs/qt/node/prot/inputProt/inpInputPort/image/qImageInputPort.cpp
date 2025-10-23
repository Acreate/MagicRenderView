#include "qImageInputPort.h"

#include <qt/varType/I_Type.h>

#include <qt/varType/I_Var.h>

Imp_StaticMetaInfo( QImageInputPort, QObject::tr( "qImage" ), QObject::tr( "inputPort" ) );
QImageInputPort::QImageInputPort( NodeItem *parent ) : NodeInputPort( parent ) {


	typePtr = new I_Type(
		typeid( t_current_type ),
		sizeof( t_current_type ),
		[] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		},
		[]( ) ->void * {
			return new t_current_type( );
		} );
	varPtr = new I_Var( typePtr, title );
	setTitle( getMetaObjectName( ) );
}
