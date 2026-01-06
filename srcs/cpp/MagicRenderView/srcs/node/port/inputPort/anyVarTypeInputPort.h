#ifndef ANYVARTYPEINPUTPORT_H_H_HEAD__FILE__
#define ANYVARTYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "inputPort.h"

class AnyVarTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	AnyVarTypeInputPort( const QString &name )
		: InputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::AnyVar;
	}
	bool init( Node *parent ) override;
};
#endif // ANYVARTYPEINPUTPORT_H_H_HEAD__FILE__
