#ifndef CACHETYPEOUTPUTPORT_H_H_HEAD__FILE__
#define CACHETYPEOUTPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "outputPort.h"

class CacheTypeOutputPort : public OutputPort {
	Q_OBJECT;
public:
	CacheTypeOutputPort( const QString &name )
		: OutputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Cache;
	}
};
#endif // CACHETYPEOUTPUTPORT_H_H_HEAD__FILE__
