#ifndef INTINPUTPORT_H_H_HEAD__FILE__
#define INTINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../inputPort.h"

class IntInputPort : public InputPort {
	Q_OBJECT;
public:
	IntInputPort( Application *const instance_ptr, VarDirector *const var_director, const QString &name, Node *const node, QWidget *const parent )
		: InputPort( instance_ptr, var_director, name, node, parent ) { }
	bool init( ) override;
};
#endif // INTINPUTPORT_H_H_HEAD__FILE__
