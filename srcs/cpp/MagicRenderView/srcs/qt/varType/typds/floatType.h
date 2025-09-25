#ifndef FLOATTYPE_H_H_HEAD__FILE__
#define FLOATTYPE_H_H_HEAD__FILE__
#pragma once

#include "../I_Type.h"
#include "../baseVarType.h"

class FloatType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class BaseVarType;
	friend class StringType;
	friend class IntType;
	friend class NullptrType;
protected:
	using t_current_type = double;
	t_current_type *var;
public:
	FloatType( QObject *parent );
	FloatType( );
	~FloatType( ) override;
	void resetVar( ) override {
		*var = t_current_type( );
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
};

#endif // FLOATTYPE_H_H_HEAD__FILE__
