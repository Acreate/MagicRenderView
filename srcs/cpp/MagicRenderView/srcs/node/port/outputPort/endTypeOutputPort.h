#ifndef ENDTYPEOUTPUTPORT_H_H_HEAD__FILE__
#define ENDTYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "outputPort.h"

class EndTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	EndTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::End;
	}
};
#endif // ENDTYPEOUTPUTPORT_H_H_HEAD__FILE__
