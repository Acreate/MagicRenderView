#ifndef LOGICTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define LOGICTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once


#include "outputPort.h"

class LogicTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	LogicTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Logic;
	}
};
#endif // LOGICTYPEOUTPUTPORT_H_H_HEAD__FILE__
