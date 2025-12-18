#ifndef INTERFACETYPEOUTPUTPORT_H_H_HEAD__FILE__
#define INTERFACETYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "outputPort.h"

class InterFaceTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	InterFaceTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::InterFace;
	}
};
#endif // INTERFACETYPEOUTPUTPORT_H_H_HEAD__FILE__
