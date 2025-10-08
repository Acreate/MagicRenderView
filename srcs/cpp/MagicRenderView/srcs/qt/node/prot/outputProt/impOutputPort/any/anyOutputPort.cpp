#include "anyOutputPort.h"
#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>
Imp_StaticMetaInfo( AnyOutputPort, QObject::tr( "any" ), QObject::tr( "output" ) );
AnyOutputPort::AnyOutputPort( NodeItem *parent ) : NodeOutputPort( parent ) {
	setTitle( getMetaObjectName( ) );
}
