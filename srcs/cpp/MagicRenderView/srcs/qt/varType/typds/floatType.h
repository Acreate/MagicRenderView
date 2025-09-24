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
	FloatType( const FloatType &other );
	~FloatType( ) override;
	void resetVar( ) override {
		*var = t_current_type( );
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
//public:
//	DEF_OPERATOR_CALCULATE( FloatType, StringType );
//	DEF_OPERATOR_CALCULATE( FloatType, IntType );
//	DEF_OPERATOR_CALCULATE( FloatType, FloatType );
//
//	DEF_FRIEND_OPERATOR_CALCULATE( IntType, StringType );
//	DEF_FRIEND_OPERATOR_CALCULATE( IntType, IntType );
//	DEF_FRIEND_OPERATOR_CALCULATE( IntType, FloatType );
//
//	DEF_FRIEND_OPERATOR_CALCULATE( StringType, StringType );
//	DEF_FRIEND_OPERATOR_CALCULATE( StringType, IntType );
//	DEF_FRIEND_OPERATOR_CALCULATE( StringType, FloatType );

};

#endif // FLOATTYPE_H_H_HEAD__FILE__
