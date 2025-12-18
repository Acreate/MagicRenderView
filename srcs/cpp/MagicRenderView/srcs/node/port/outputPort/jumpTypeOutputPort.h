#ifndef JUMPTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define JUMPTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "outputPort.h"

class JumpTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	JumpTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Jump;
	}
};
#endif // JUMPTYPEOUTPUTPORT_H_H_HEAD__FILE__
