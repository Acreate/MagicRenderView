#ifndef INTTYPE_H_H_HEAD__FILE__
#define INTTYPE_H_H_HEAD__FILE__
#pragma once
#include "../baseVarType.h"

class IntType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class BaseVarType;
	friend class StringType;
	friend class FloatType;
	friend class NullptrType;
protected:
	using t_current_type = int64_t;
	t_current_type *var;
public:
	IntType( QObject *parent );
	IntType( ) : IntType( nullptr ) { }
	~IntType( ) override {
		delete var;
	}
	void resetVar( ) override {
		*var = t_current_type( );
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
};
#endif // INTTYPE_H_H_HEAD__FILE__
