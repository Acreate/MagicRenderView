#include "pointTypeOutputPort.h"
#include <enums/nodeEnum.h>
PointTypeOutputPort::PointTypeOutputPort( const QString &name ): OutputPort( name ) { }
NodeEnum::PortType PointTypeOutputPort::getPortType( ) const {
	return NodeEnum::PortType::Point;
}
