#ifndef INTTYPE_H_H_HEAD__FILE__
#define INTTYPE_H_H_HEAD__FILE__
#pragma once
#include "../baseVarType.h"

class IntType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class StringType;
	friend class FloatType;
protected:
	using t_current_type = int64_t;
	t_current_type *var;
protected:
	IntType( QObject *parent );
	IntType( ) : IntType( nullptr ) { }
public:
	~IntType( ) override {
		delete var;
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
public:
	DEF_OPERATOR_CALCULATE( IntType, StringType );
	DEF_OPERATOR_CALCULATE( IntType, IntType );
	DEF_OPERATOR_CALCULATE( IntType, FloatType );

	DEF_FRIEND_OPERATOR_CALCULATE( StringType, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE( StringType, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE( StringType, FloatType );

	DEF_FRIEND_OPERATOR_CALCULATE( FloatType, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE( FloatType, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE( FloatType, FloatType );
};
#endif // INTTYPE_H_H_HEAD__FILE__
