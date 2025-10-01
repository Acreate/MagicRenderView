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
	size_t memorySize;
	/// @brief 释放函数
	std_function< bool( void *p ) > release;
	/// @brief 创建函数
	std_function< bool( void *&p ) > create;
	I_Type( ) = delete;
public:
	I_Type( const type_info &type_info )
		: typeInfo( type_info ) {
		memorySize = 0;
		release = nullptr;
		create = nullptr;
	}
	I_Type( const type_info &type_info, const size_t &memory_size, const std_function< bool( void *p ) > &release, const std_function< bool( void *&p ) > &create )
		: typeInfo( type_info ),
		memorySize( memory_size ),
		release( release ),
		create( create ) { }
	friend bool operator==( const I_Type &lhs, const I_Type &rhs ) {
		return lhs.typeInfo == rhs.typeInfo
			&& lhs.memorySize == rhs.memorySize;
	}
	friend bool operator!=( const I_Type &lhs, const I_Type &rhs ) { return !( lhs == rhs ); }
	virtual ~I_Type( ) { }
	virtual const type_info & getTypeInfo( ) const { return typeInfo; }
	virtual size_t getMemorySize( ) const { return memorySize; }
	virtual const std_function< bool( void *p ) > & getRelease( ) const { return release; }
	virtual const std_function< bool( void *&p ) > & getCreate( ) const { return create; }
};

#endif // I_TYPE_H_H_HEAD__FILE__
