#ifndef I_VAR_H_H_HEAD__FILE__
#define I_VAR_H_H_HEAD__FILE__
#pragma once
#include "I_Conver.h"
#include "I_Type.h"

/// @brief 变量接口
class I_Var {
protected:
	I_Type typeInfo;
	void *varPtr;
protected:
	virtual void * data( const I_Type &target_type_info );
public:
	I_Var( );
	I_Var( const I_Var &other ) = delete;
	virtual ~I_Var( ) = default;
	virtual I_Var & operator=( const I_Var &other ) = delete;
	friend bool operator==( const I_Var &lhs, const I_Var &rhs );
	friend bool operator!=( const I_Var &lhs, const I_Var &rhs );
	template< typename ttype >
	ttype * ptr( ) const {
		return ( ttype * ) this->data( typeid( ttype ) );
	}
};

#endif // I_VAR_H_H_HEAD__FILE__
