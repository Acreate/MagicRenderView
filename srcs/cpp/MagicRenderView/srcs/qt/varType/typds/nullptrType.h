#ifndef NULLPTRTYPE_H_H_HEAD__FILE__
#define NULLPTRTYPE_H_H_HEAD__FILE__
#pragma once

#include "../I_Type.h"
#include "../baseVarType.h"

class NullptrType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class StringType;
	friend class IntType;
	friend class FloatType;
protected:
	NullptrType( QObject *parent );
	NullptrType( ) : NullptrType( nullptr ) { }
	NullptrType( const NullptrType &other )
		: BaseVarType { other } { }
public:
	~NullptrType( ) override;
protected:
	void * getVarPtr( ) const override {
		return nullptr;
	}
public:
	bool operator !=( const NullptrType &right_type_var_ref ) const { return !( *this == right_type_var_ref ); }
	bool operator ==( const NullptrType &right_type_var_ref ) const;
public:
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( NullptrType, StringType, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( NullptrType, IntType, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( NullptrType, FloatType, FloatType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( StringType, NullptrType, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( IntType, NullptrType, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( FloatType, NullptrType, FloatType );

	DEF_EQU_OPERATOR_CALCULATE( NullptrType, StringType );
	DEF_EQU_OPERATOR_CALCULATE( NullptrType, FloatType );
	DEF_EQU_OPERATOR_CALCULATE( NullptrType, IntType );
	DEF_EQU_OPERATOR_CALCULATE( NullptrType, BaseVarType );

	DEF_ASSIGN_OPERATOR_CALCULATE( NullptrType, StringType );
	DEF_ASSIGN_OPERATOR_CALCULATE( NullptrType, IntType );
	DEF_ASSIGN_OPERATOR_CALCULATE( NullptrType, FloatType );
};
#endif // NULLPTRTYPE_H_H_HEAD__FILE__
