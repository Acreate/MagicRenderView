#ifndef INTVECTOROUTPUTPORT_H_H_HEAD__FILE__
#define INTVECTOROUTPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../outputPort.h"

class IntVectorOutputPort : public OutputPort {
	Q_OBJECT;
public:
	IntVectorOutputPort( Application *instance_ptr, VarDirector *var_director, const QString &name, Node *node, QObject *parent )
		: OutputPort( instance_ptr, var_director, name, node, parent ) { }
	bool init( ) override {
		return true;
	}
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Array;
	}
};
#endif // INTVECTOROUTPUTPORT_H_H_HEAD__FILE__
