#include "dynamicTypeOutputPort.h"
DynamicTypeOutputPort::DynamicTypeOutputPort( const NodeEnum::PortType &port_enum_type, const QString &name, const QString &output_potr_type_name ): OutputPort( name ), portType( port_enum_type ) {
	OutputPort::varTypeName = output_potr_type_name;
}
NodeEnum::PortType DynamicTypeOutputPort::getPortType( ) const {
	return portType;
}
bool DynamicTypeOutputPort::init( Node *parent ) {
	if( OutputPort::init( parent ) == false )
		return false;
	return true;
}
