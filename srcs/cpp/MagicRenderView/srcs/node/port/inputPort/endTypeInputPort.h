#ifndef ENDTYPEINPUTPORT_H_H_HEAD__FILE__
#define ENDTYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "inputPort.h"

class EndTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	EndTypeInputPort( const QString &name )
		: InputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::End;
	}
};
#endif // ENDTYPEINPUTPORT_H_H_HEAD__FILE__
