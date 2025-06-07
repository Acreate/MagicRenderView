#ifndef BASESTACKEX_H_H_HEAD__FILE__
#define BASESTACKEX_H_H_HEAD__FILE__
#pragma once
#include "baseStack.h"

class BaseStackEx : public BaseStack {
	Q_OBJECT;
public:
	friend class IVarStack;
protected:
	BaseStackEx( ) { }
	ITypeObject * generateUBVar( const QString &type_name ) const override;
public:
	~BaseStackEx( ) override {
		
	}
};

#endif // BASESTACKEX_H_H_HEAD__FILE__
