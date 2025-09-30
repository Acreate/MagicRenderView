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
	std_function< bool( ) > isDeletePtr;
	void *p;
	I_Type( ) = delete;
public:
	/// @brief 类型识别包装器
	/// @param type_info 类型，使用 typeid 获取
	/// @param p 指向类型的对象的指针
	/// @param is_delete_ptr 描述该指针对象是否被释放（它应该是一个动态的识别器，p 指向释放之前 false，p 释放之后返回 true）
	I_Type( const type_info &type_info, void *p, const std_function< bool( ) > &is_delete_ptr )
		: typeInfo( type_info ),
		isDeletePtr( is_delete_ptr ),
		p( p ) { }
	I_Type( const I_Type &other )
		: typeInfo { other.typeInfo },
		isDeletePtr { other.isDeletePtr },
		p { other.p } { }
	I_Type & operator=( const I_Type &other ) : typeInfo( other.typeInfo ) {
		if( this == &other )
			return *this;
		isDeletePtr = other.isDeletePtr;
		p = other.p;
		return *this;
	}
	friend bool operator==( const I_Type &lhs, const I_Type &rhs ) {
		return lhs.typeInfo == rhs.typeInfo
			&& lhs.p == rhs.p;
	}
	friend bool operator!=( const I_Type &lhs, const I_Type &rhs ) { return !( lhs == rhs ); }
	virtual ~I_Type( ) { }
	virtual const type_info & getTypeInfo( ) const { return typeInfo; }
	virtual void * getPtr( ) const { return p; }
	virtual void setPtr( void *const set_ptr ) { p = set_ptr; }
	/// @brief 指向内容是否被释放
	/// @return 返回 true 表示已经被释放
	virtual bool isDeleteVarPtr( ) const { return isDeletePtr( ); }
	virtual const std_function< bool( ) > & getDeleteVarPtr( ) const { return isDeletePtr; }

};

#endif // I_TYPE_H_H_HEAD__FILE__
