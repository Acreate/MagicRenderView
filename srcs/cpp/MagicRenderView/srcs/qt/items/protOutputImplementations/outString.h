#ifndef OUTSTRING_H_H_HEAD__FILE__
#define OUTSTRING_H_H_HEAD__FILE__
#pragma once
#include "../protOutputItemWidget.h"

class OutString : public ProtOutputItemWidget {
	Q_OBJECT;
public:
	OutString( QWidget *parent, const std_shared_ptr< VarType > &bind_var );
};

#endif // OUTSTRING_H_H_HEAD__FILE__
