#ifndef ANYOUTPUTPORT_H_H_HEAD__FILE__
#define ANYOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../anyTypeOutputPort.h"
#include "../outputPort.h"

class AnyOutputPort : public AnyTypeOutputPort {
	Q_OBJECT;
public:
	AnyOutputPort( const QString &name )
		: AnyTypeOutputPort( name ) { }
	bool init( Node *parent ) override;
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Any;
	}
};

#endif // ANYOUTPUTPORT_H_H_HEAD__FILE__
