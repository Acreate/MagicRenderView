#ifndef STRINGTYPE_H_H_HEAD__FILE__
#define STRINGTYPE_H_H_HEAD__FILE__
#pragma once

#include "../baseVarType.h"
class StringType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class FloatType;
	friend class IntType;
protected:
	using t_current_type = QString;
	t_current_type *var;
protected:
	StringType( QObject *parent );
	StringType( ) : StringType( nullptr ) { }
public:
	~StringType( ) override {
		delete var;
	}
protected:
	void * getVarPtr( ) const override {
		return var;
	}
public:

	DEF_ASSIGN_OPERATOR_CALCULATE( StringType, FloatType);
	DEF_ASSIGN_OPERATOR_CALCULATE( StringType, IntType);
	DEF_ASSIGN_OPERATOR_CALCULATE( StringType, StringType);
	
	DEF_FRIEND_OPERATOR_CALCULATE( FloatType, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE( FloatType, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE( FloatType, FloatType );

	DEF_FRIEND_OPERATOR_CALCULATE( IntType, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE( IntType, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE( IntType, FloatType );
};
#endif // STRINGTYPE_H_H_HEAD__FILE__
