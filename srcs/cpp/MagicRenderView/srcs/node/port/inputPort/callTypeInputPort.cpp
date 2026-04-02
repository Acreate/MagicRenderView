#include "callTypeInputPort.h"
#include <enums/nodeEnum.h>
CallTypeInputPort::CallTypeInputPort( const QString &name ): InputPort( name ) { }
NodeEnum::PortType CallTypeInputPort::getPortType( ) const {
	return NodeEnum::PortType::Call;
}
