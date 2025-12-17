#ifndef GENERATETYPEINPUTPORT_H_H_HEAD__FILE__
#define GENERATETYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once


#include "inputPort.h"

class GenerateTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	GenerateTypeInputPort( const QString &name )
		: InputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Generate;
	}
};
#endif // GENERATETYPEINPUTPORT_H_H_HEAD__FILE__
