#include "toPointTypeOutputPort.h"
#include <enums/nodeEnum.h>
ToPointTypeOutputPort::ToPointTypeOutputPort( const QString &name ): OutputPort( name ) { }
NodeEnum::PortType ToPointTypeOutputPort::getPortType( ) const {
	return NodeEnum::PortType::ToPoint;
}
