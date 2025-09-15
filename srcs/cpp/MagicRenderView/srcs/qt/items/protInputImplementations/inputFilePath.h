#ifndef INPUTFILEPATH_H_H_HEAD__FILE__
#define INPUTFILEPATH_H_H_HEAD__FILE__
#pragma once
#include "../protInputItemWidget.h"

class InputFilePath : public ProtInputItemWidget {
	Q_OBJECT;
public:
	InputFilePath( QWidget *parent, VarType *bind_var );
};

#endif // INPUTFILEPATH_H_H_HEAD__FILE__
