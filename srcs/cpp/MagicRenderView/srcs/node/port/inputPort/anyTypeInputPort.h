#ifndef ANYTYPEINPUTPORT_H_H_HEAD__FILE__
#define ANYTYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "inputPort.h"

class AnyTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	AnyTypeInputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Any;
	}
};

#endif // ANYTYPEINPUTPORT_H_H_HEAD__FILE__
