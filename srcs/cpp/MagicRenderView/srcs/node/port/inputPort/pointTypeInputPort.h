#ifndef POINTTYPEINPUTPORT_H_H_HEAD__FILE__
#define POINTTYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "inputPort.h"

class PointTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	PointTypeInputPort( const QString &name )
		: InputPort( name ) { }

	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Point;
	}
};
#endif // POINTTYPEINPUTPORT_H_H_HEAD__FILE__
