#ifndef I_TYPE_H_H_HEAD__FILE__
#define I_TYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../alias/type_alias.h"

class I_Stack;
/// @brief 类型接口
class I_Type {
protected:
	const type_info &typeInfo;
	I_Type( ) = delete;
public:
	/// @brief 类型识别包装器
	/// @param type_info 类型，使用 typeid 获取
	I_Type( const type_info &type_info )
		: typeInfo( type_info ) { }
	I_Type( const I_Type &other )
		: typeInfo { other.typeInfo } { }
	friend bool operator==( const I_Type &lhs, const I_Type &rhs ) {
		return lhs.typeInfo == rhs.typeInfo;
	}
	friend bool operator!=( const I_Type &lhs, const I_Type &rhs ) { return !( lhs == rhs ); }
	virtual ~I_Type( ) { }
	virtual const type_info & getTypeInfo( ) const { return typeInfo; }

};

#endif // I_TYPE_H_H_HEAD__FILE__
