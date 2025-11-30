#ifndef ARRAYTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define ARRAYTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "outputPort.h"

class ArrayTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	ArrayTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Array;
	}
};

#endif // ARRAYTYPEOUTPUTPORT_H_H_HEAD__FILE__
