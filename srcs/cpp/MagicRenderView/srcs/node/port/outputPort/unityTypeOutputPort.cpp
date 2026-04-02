#include "unityTypeOutputPort.h"
#include <enums/nodeEnum.h>
UnityTypeOutputPort::UnityTypeOutputPort( const QString &name ): OutputPort( name ) { }
NodeEnum::PortType UnityTypeOutputPort::getPortType( ) const {
	return NodeEnum::PortType::Unity;
}
