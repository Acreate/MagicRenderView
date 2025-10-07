#include "binOutputPort.h"

#include <qt/varType/I_Type.h>

#include <qt/varType/I_Var.h>
Imp_StaticMetaInfo( BinOutputPort, QObject::tr( "bin" ), QObject::tr( "output" ) );
BinOutputPort::BinOutputPort( NodeItem *parent ) : NodeOutputPort( parent ) {

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
