#ifndef BEGINTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define BEGINTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once


#include "outputPort.h"

class BeginTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	BeginTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Beg;
	}
};
#endif // BEGINTYPEOUTPUTPORT_H_H_HEAD__FILE__
