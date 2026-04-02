#include "anyVarTypeOutputPort.h"

#include "../../../app/application.h"
#include "../../../director/varDirector.h"
#include <enums/nodeEnum.h>
AnyVarTypeOutputPort::AnyVarTypeOutputPort( const QString &name ): OutputPort( name ) { }
NodeEnum::PortType AnyVarTypeOutputPort::getPortType( ) const {
	return NodeEnum::PortType::AnyVar;
}
bool AnyVarTypeOutputPort::init( Node *parent ) {
	if( OutputPort::init( parent ) == false )
		return false;
	if(  Application::getInstancePtr( )->getVarDirector( )->getTypeName( typeid( void * ), varTypeName ) == false )
		return false;
	return true;
}
