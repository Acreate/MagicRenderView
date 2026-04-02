#include "arrayTypeInputPort.h"
#include <enums/nodeEnum.h>
ArrayTypeInputPort::ArrayTypeInputPort( const QString &name ): InputPort( name ) { }
NodeEnum::PortType ArrayTypeInputPort::getPortType( ) const {
	return NodeEnum::PortType::Array;
}
