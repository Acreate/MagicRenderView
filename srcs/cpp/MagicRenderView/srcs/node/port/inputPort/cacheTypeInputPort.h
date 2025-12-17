#ifndef CACHETYPEINPUTPORT_H_H_HEAD__FILE__
#define CACHETYPEINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "inputPort.h"

class CacheTypeInputPort : public InputPort {
	Q_OBJECT;
public:
	CacheTypeInputPort( const QString &name )
		: InputPort( name ) { }
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Cache;
	}
};
#endif // CACHETYPEINPUTPORT_H_H_HEAD__FILE__
