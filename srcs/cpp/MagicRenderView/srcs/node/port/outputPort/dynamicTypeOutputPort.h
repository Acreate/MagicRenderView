#ifndef DYNAMICTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define DYNAMICTYPEOUTPUTPORT_H_H_HEAD__FILE__

#include "outputPort.h"

class DynamicTypeOutputPort : public OutputPort {

	Q_OBJECT;
private:
	OutputPortFrinedClass( );
protected:
	NodeEnum::PortType portType;
protected:
	DynamicTypeOutputPort( const NodeEnum::PortType &port_enum_type, const QString &name, const QString &output_potr_type_name )
		: OutputPort( name ), portType( port_enum_type ) {
		OutputPort::varTypeName = output_potr_type_name;
	}
public:
	NodeEnum::PortType getPortType( ) const override {
		return portType;
	}
	bool init( Node *parent ) override;
};
#endif // DYNAMICTYPEOUTPUTPORT_H_H_HEAD__FILE__
