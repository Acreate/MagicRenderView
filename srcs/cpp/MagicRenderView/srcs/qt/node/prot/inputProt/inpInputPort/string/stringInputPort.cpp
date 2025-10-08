#include "./stringInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>
Imp_StaticMetaInfo( StringInputPort, QObject::tr( "string" ), QObject::tr( "inputPort" ) );
StringInputPort::StringInputPort( NodeItem *parent ) : NodeInputPort( parent ) {
	typePtr = new I_Type(
		typeid( t_current_type ),
		sizeof( t_current_type ),
		[] ( void *p ) {
			delete ( t_current_type * ) p;
			return true;
		},
		[] ( void *&p ) {
			p = new t_current_type( );
			return true;
		} );
	varPtr = new I_Var( typePtr, title );
	setTitle( getMetaObjectName( ) );
}
