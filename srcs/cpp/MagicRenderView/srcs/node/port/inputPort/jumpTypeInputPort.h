#ifndef JUMPTYPEINPUTPORT_H_H_HEAD__FILE__
#define JUMPTYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once


#include "inputPort.h"

class JumpTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	JumpTypeInputPort( const QString &name )
		: InputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Jump;
	}
};
#endif // JUMPTYPEINPUTPORT_H_H_HEAD__FILE__
