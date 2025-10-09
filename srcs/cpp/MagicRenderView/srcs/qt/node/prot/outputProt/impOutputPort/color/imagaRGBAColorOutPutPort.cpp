#include "imagaRGBAColorOutPutPort.h"

#include <qt/varType/I_Type.h>

#include <qt/varType/I_Var.h>

Imp_StaticMetaInfo( ImagaRGBAColorOutPutPort, QObject::tr( "imageRGBA" ), QObject::tr( "output" ) );
ImagaRGBAColorOutPutPort::ImagaRGBAColorOutPutPort( NodeItem *parent ) : NodeOutputPort( parent ) {


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
