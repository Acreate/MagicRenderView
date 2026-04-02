#include "arrayTypeOutputPort.h"
#include <enums/nodeEnum.h>
ArrayTypeOutputPort::ArrayTypeOutputPort( const QString &name ): OutputPort( name ) { }
NodeEnum::PortType ArrayTypeOutputPort::getPortType( ) const {
	return NodeEnum::PortType::Array;
}
