#include "functionTypeOutputPort.h"
#include <enums/nodeEnum.h>
FunctionTypeOutputPort::FunctionTypeOutputPort( const QString &name ): OutputPort( name ) { }
NodeEnum::PortType FunctionTypeOutputPort::getPortType( ) const {
	return NodeEnum::PortType::Function;
}
