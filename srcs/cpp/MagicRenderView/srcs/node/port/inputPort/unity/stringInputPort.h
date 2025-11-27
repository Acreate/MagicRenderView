#ifndef STRINGINPUTPORT_H_H_HEAD__FILE__
#define STRINGINPUTPORT_H_H_HEAD__FILE__
#pragma once

#include "../inputPort.h"

class StringInputPort : public InputPort {
	Q_OBJECT;
public:
	StringInputPort( Application *const instance_ptr, VarDirector *const var_director, const QString &name, Node *const node, QWidget *const parent )
		: InputPort( instance_ptr, var_director, name, node, parent ) { }
	bool init( ) override;
};

#endif // STRINGINPUTPORT_H_H_HEAD__FILE__
