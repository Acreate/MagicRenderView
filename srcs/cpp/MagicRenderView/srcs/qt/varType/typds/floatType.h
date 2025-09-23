#ifndef FLOATTYPE_H_H_HEAD__FILE__
#define FLOATTYPE_H_H_HEAD__FILE__
#pragma once

#include "../I_Type.h"
#include "../baseVarType.h"

class FloatType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class StringType;
	friend class IntType;
protected:
	using t_current_type = double;
	t_current_type *var;
protected:
	FloatType( QObject *parent );
	FloatType( );
public:
	~FloatType( ) override;
	FloatType( const FloatType &other )
		: BaseVarType { other }, var { new t_current_type( *other.var ) } { }
protected:
	void * getVarPtr( ) const override {
		return var;
	}
public:
	DEF_OPERATOR_CALCULATE( FloatType, StringType );
	DEF_OPERATOR_CALCULATE( FloatType, IntType );
	DEF_OPERATOR_CALCULATE( FloatType, FloatType );

	DEF_FRIEND_OPERATOR_CALCULATE( IntType, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE( IntType, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE( IntType, FloatType );

	DEF_FRIEND_OPERATOR_CALCULATE( StringType, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE( StringType, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE( StringType, FloatType );

};

#endif // FLOATTYPE_H_H_HEAD__FILE__
