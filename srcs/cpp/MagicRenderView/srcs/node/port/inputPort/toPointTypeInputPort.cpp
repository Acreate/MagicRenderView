#include "toPointTypeInputPort.h"
#include <enums/nodeEnum.h>
ToPointTypeInputPort::ToPointTypeInputPort( const QString &name ): InputPort( name ) { }
NodeEnum::PortType ToPointTypeInputPort::getPortType( ) const {
	return NodeEnum::PortType::ToPoint;
}
