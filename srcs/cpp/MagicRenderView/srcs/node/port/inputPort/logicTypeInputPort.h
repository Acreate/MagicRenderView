#ifndef LOGICTYPEINPUTPORT_H_H_HEAD__FILE__
#define LOGICTYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "inputPort.h"

class LogicTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	LogicTypeInputPort( const QString &name )
		: InputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Logic;
	}
};
#endif // LOGICTYPEINPUTPORT_H_H_HEAD__FILE__
