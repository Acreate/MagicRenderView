#include "anyVarTypeInputPort.h"

#include <enums/nodeEnum.h>
#include "../../../app/application.h"
#include "../../../director/varDirector.h"
AnyVarTypeInputPort::AnyVarTypeInputPort( const QString &name ): InputPort( name ) { }
NodeEnum::PortType AnyVarTypeInputPort::getPortType( ) const {
	return NodeEnum::PortType::AnyVar;
}
bool AnyVarTypeInputPort::init( Node *parent ) {
	if( InputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( void * ), varTypeName ) == false )
		return false;
	return true;
}
