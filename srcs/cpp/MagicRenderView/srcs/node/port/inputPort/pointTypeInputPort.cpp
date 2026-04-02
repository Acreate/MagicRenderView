#include "pointTypeInputPort.h"
#include <enums/nodeEnum.h>
PointTypeInputPort::PointTypeInputPort( const QString &name ): InputPort( name ) { }
NodeEnum::PortType PointTypeInputPort::getPortType( ) const {
	return NodeEnum::PortType::Point;
}
