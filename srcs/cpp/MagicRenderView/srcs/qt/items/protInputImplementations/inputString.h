#ifndef INPUTSTRING_H_H_HEAD__FILE__
#define INPUTSTRING_H_H_HEAD__FILE__
#pragma once
#include "../protInputItemWidget.h"

class InputString : public ProtInputItemWidget {
	Q_OBJECT;
public:
	InputString( QWidget *parent, VarType *bind_var );
};

#endif // INPUTSTRING_H_H_HEAD__FILE__
