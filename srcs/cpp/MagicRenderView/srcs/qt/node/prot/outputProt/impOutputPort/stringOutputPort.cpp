#include "./stringOutputPort.h"

#include <QPainter>

#include <qt/application/application.h>

#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>
Imp_StaticMetaInfo( StringOutputPort, QObject::tr( "StringOutputPort" ), QObject::tr( "impOutputPort" ) );
StringOutputPort::StringOutputPort( NodeItem *parent ) : NodeOutputPort( parent ) {

	typePtr = new I_Type(
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
	varPtr = new I_Var( typePtr, title );
	setTitle( getMetaObjectName( ) );
}
