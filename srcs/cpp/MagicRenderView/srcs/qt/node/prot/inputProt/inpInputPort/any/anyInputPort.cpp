#include "anyInputPort.h"
#include <qt/varType/I_Type.h>

#include <qt/varType/I_Var.h>
Imp_StaticMetaInfo( AnyInputPort, QObject::tr( "any" ), QObject::tr( "inputPort" ) );
AnyInputPort::AnyInputPort( NodeItem *parent ) : NodeInputPort( parent ) {
	setTitle( getMetaObjectName( ) );
}
