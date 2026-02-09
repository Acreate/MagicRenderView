#ifndef DYNAMICTYPEINPUTPORT_H_H_HEAD__FILE__
#define DYNAMICTYPEINPUTPORT_H_H_HEAD__FILE__

#include "inputPort.h"

namespace NodeEnum {
	enum class PortType;
}
class DynamicTypeInputPort : public InputPort {
	Q_OBJECT;
private:
	InputPortFrinedClass( );
protected:
	NodeEnum::PortType portType;
protected:
	DynamicTypeInputPort( const NodeEnum::PortType &port_enum_type, const QString &name, const QString &input_port_type_name )
		: InputPort( name ), portType( port_enum_type ) {
		InputPort::varTypeName = input_port_type_name;
	}
public:
	NodeEnum::PortType getPortType( ) const override {
		return portType;
	}
	bool init( Node *parent ) override;
};
#endif // DYNAMICTYPEINPUTPORT_H_H_HEAD__FILE__
