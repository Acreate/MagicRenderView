#ifndef ARRAYTYPEINPUTPORT_H_H_HEAD__FILE__
#define ARRAYTYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "inputPort.h"

class ArrayTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	ArrayTypeInputPort( const QString &name )
		: InputPort( name ) { }

	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Array;
	}
};
#endif // ARRAYTYPEINPUTPORT_H_H_HEAD__FILE__
