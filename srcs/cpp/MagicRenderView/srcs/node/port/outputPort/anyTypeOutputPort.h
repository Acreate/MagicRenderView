#ifndef ANYTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define ANYTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "outputPort.h"

class AnyTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	AnyTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Any;
	}
};

#endif // ANYTYPEOUTPUTPORT_H_H_HEAD__FILE__
