#ifndef GENERATETYPEOUTPUTPORT_H_H_HEAD__FILE__
#define GENERATETYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once


#include "outputPort.h"

class GenerateTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	GenerateTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Generate;
	}
};
#endif // GENERATETYPEOUTPUTPORT_H_H_HEAD__FILE__
