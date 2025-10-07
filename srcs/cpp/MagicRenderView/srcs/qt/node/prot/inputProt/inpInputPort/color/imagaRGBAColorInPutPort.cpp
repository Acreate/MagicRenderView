#include "imagaRGBAColorInPutPort.h"

#include <qt/varType/I_Type.h>

#include <qt/varType/I_Var.h>

Imp_StaticMetaInfo( ImagaRGBAColorInPutPort, QObject::tr( "imageRGBA" ), QObject::tr( "inputPort" ) );
ImagaRGBAColorInPutPort::ImagaRGBAColorInPutPort( NodeItem *parent ) : NodeInputPort( parent ) {

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
