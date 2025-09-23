#ifndef I_NEW_H_H_HEAD__FILE__
#define I_NEW_H_H_HEAD__FILE__
#pragma once
#include "I_Type.h"

class I_Var;
class I_New {
protected:
	I_Type typeInfo;
public:
	I_New( const I_Type &type_info )
		: typeInfo( type_info ) { }
	virtual ~I_New( ) = default;
	virtual const I_Type & getTypeInfo( ) const { return typeInfo; }
	virtual bool newObj( I_Var **ptr ) const = 0;
};

#endif // I_NEW_H_H_HEAD__FILE__
