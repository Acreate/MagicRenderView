#include "unityTypeInputPort.h"
#include <enums/nodeEnum.h>
UnityTypeInputPort::UnityTypeInputPort( const QString &name ): InputPort( name ) { }
NodeEnum::PortType UnityTypeInputPort::getPortType( ) const {
	return NodeEnum::PortType::Unity;
}
