#ifndef FLOATINPUTPORT_H_H_HEAD__FILE__
#define FLOATINPUTPORT_H_H_HEAD__FILE__
#pragma once
#include "../inputPort.h"

class FloatInputPort : public InputPort {
	Q_OBJECT;
public:
	FloatInputPort( Application *const instance_ptr, VarDirector *const var_director, const QString &name, Node *const node, QWidget *const parent )
		: InputPort( instance_ptr, var_director, name, node, parent ) { }
	bool init( ) override {
		return true;
	}
	NodeEnum::PortType getPortType( ) const override {
		return NodeEnum::PortType::Unity;
	}
};

#endif // FLOATINPUTPORT_H_H_HEAD__FILE__
