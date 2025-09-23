#ifndef INTTYPE_H_H_HEAD__FILE__
#define INTTYPE_H_H_HEAD__FILE__
#pragma once
#include "../baseVarType.h"

class IntType : public BaseVarType {
	Q_OBJECT;
protected:
	using t_current_type = int64_t;
	t_current_type *var;
public:
	IntType( QObject *parent );
	~IntType( ) override {
		delete var;
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
};
#endif // INTTYPE_H_H_HEAD__FILE__
