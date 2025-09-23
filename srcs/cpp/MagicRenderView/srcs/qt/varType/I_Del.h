#ifndef I_DEL_H_H_HEAD__FILE__
#define I_DEL_H_H_HEAD__FILE__
#pragma once
#include "I_Type.h"

class I_Var;
class I_Del {
protected:
	I_Type typeInfo;
public:
	I_Del( const I_Type &type_info )
		: typeInfo( type_info ) { }
	virtual ~I_Del( ) = default;
	virtual const I_Type & getTypeInfo( ) const { return typeInfo; }
	virtual bool delObj( I_Var **ptr ) const = 0;
};
#endif // I_DEL_H_H_HEAD__FILE__
