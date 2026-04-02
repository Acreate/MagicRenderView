#include "callTypeOutputPort.h"
#include <enums/nodeEnum.h>
CallTypeOutputPort::CallTypeOutputPort( const QString &name ): OutputPort( name ) { }
NodeEnum::PortType CallTypeOutputPort::getPortType( ) const {
	return NodeEnum::PortType::Call;
}
