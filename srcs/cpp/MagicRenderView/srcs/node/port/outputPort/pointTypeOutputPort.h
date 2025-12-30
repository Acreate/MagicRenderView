#ifndef POINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define POINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "outputPort.h"

class PointTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	PointTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Point;
	}
};
#endif // POINTTYPEOUTPUTPORT_H_H_HEAD__FILE__
