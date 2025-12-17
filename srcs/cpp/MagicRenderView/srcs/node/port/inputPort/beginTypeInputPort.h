#ifndef BEGINTYPEINPUTPORT_H_H_HEAD__FILE__
#define BEGINTYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "inputPort.h"

class BeginTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	BeginTypeInputPort( const QString &name );
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Beg;
	}
};

#endif // BEGINTYPEINPUTPORT_H_H_HEAD__FILE__
