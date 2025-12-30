#ifndef TOBEGINTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define TOBEGINTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "outputPort.h"

class ToBeginTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	ToBeginTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::ToBegin;
	}
};
#endif // TOBEGINTYPEOUTPUTPORT_H_H_HEAD__FILE__
