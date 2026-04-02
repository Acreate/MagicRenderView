#include "dynamicTypeInputPort.h"
DynamicTypeInputPort::DynamicTypeInputPort( const NodeEnum::PortType &port_enum_type, const QString &name, const QString &input_port_type_name ): InputPort( name ), portType( port_enum_type ) {
	InputPort::varTypeName = input_port_type_name;
}
NodeEnum::PortType DynamicTypeInputPort::getPortType( ) const {
	return portType;
}
bool DynamicTypeInputPort::init( Node *parent ) {
	if( InputPort::init( parent ) == false )
		return false;
	return true;
}
