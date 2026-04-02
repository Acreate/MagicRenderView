#include "functionTypeInputPort.h"
#include <enums/nodeEnum.h>
FunctionTypeInputPort::FunctionTypeInputPort( const QString &name ): InputPort( name ) { }
NodeEnum::PortType FunctionTypeInputPort::getPortType( ) const {
	return NodeEnum::PortType::Function;
}
