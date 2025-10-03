#include "./stringInputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>
Imp_StaticMetaInfo( StringInputPort, QObject::tr( "StringInputPort" ), QObject::tr( "impInputPort" ) );
StringInputPort::StringInputPort( NodeItem *parent ) : NodeInputPort( parent ) {
	auto type = new I_Type(
		typeid( QString ),
		sizeof( QString ),
		[] ( void *p ) {
			delete ( QString * ) p;
			return true;
		},
		[] ( void *&p ) {
			p = new QString( );
			return true;
		} );
	var = std_shared_ptr< I_Var >( new I_Var( std_shared_ptr< I_Type >( type ), title ) );
	setTitle( getMetaObjectName( ) );
}
