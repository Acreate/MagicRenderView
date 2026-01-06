#ifndef ANYVARTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define ANYVARTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "outputPort.h"

class AnyVarTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	AnyVarTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::AnyVar;
	}
	bool init( Node *parent ) override;
};
#endif // ANYVARTYPEOUTPUTPORT_H_H_HEAD__FILE__
