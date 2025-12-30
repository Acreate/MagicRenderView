#ifndef TOPOINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define TOPOINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "outputPort.h"

class ToPointTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	ToPointTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::ToPoint;
	}
};
#endif // TOPOINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
