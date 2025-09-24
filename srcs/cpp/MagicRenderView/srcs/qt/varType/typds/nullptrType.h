#ifndef NULLPTRTYPE_H_H_HEAD__FILE__
#define NULLPTRTYPE_H_H_HEAD__FILE__
#pragma once

#include "../I_Type.h"
#include "../baseVarType.h"

class NullptrType : public BaseVarType {
	Q_OBJECT;
protected:
	friend class VarGenerate;
	friend class IntType;
	friend class BaseVarType;
	friend class StringType;
	friend class FloatType;
	friend class NullptrType;
public:
	NullptrType( QObject *parent );
	NullptrType( );
	NullptrType( const NullptrType &other );
public:
	~NullptrType( ) override;
protected:
	void * getVarPtr( ) const override {
		return nullptr;
	}
public:
	void resetVar( ) override { }
	bool operator !=( const NullptrType &right_type_var_ref ) const { return !( *this == right_type_var_ref ); }
	bool operator ==( const NullptrType &right_type_var_ref ) const;
public:
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const NullptrType&, const StringType&, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const NullptrType&, const IntType&, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const NullptrType&, const FloatType&, FloatType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const StringType&, const NullptrType&, StringType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const IntType&, const NullptrType&, IntType );
	DEF_FRIEND_OPERATOR_CALCULATE_SET_RESULT( const FloatType&, const NullptrType&, FloatType );

	DEF_EQU_OPERATOR_CALCULATE( const NullptrType&, const StringType & );
	DEF_EQU_OPERATOR_CALCULATE( const NullptrType&, const FloatType & );
	DEF_EQU_OPERATOR_CALCULATE( const NullptrType&, const IntType & );
	DEF_EQU_OPERATOR_CALCULATE( const NullptrType&, const BaseVarType & );

	DEF_ASSIGN_OPERATOR_CALCULATE( NullptrType&, StringType& );
	DEF_ASSIGN_OPERATOR_CALCULATE( NullptrType&, IntType & );
	DEF_ASSIGN_OPERATOR_CALCULATE( NullptrType&, FloatType& );

};
#endif // NULLPTRTYPE_H_H_HEAD__FILE__
