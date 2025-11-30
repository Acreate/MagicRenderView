#ifndef UNITYTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define UNITYTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "outputPort.h"

class UnityTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	UnityTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Unity;
	}
};

#endif // UNITYTYPEOUTPUTPORT_H_H_HEAD__FILE__
