#ifndef I_TYPE_H_H_HEAD__FILE__
#define I_TYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../alias/type_alias.h"

class I_Stack;
/// @brief 类型接口
class I_Type {
	friend class I_Type_Using_Type_Name;
public:
protected:
	const type_info &typeInfo;
	size_t memorySize;
	/// @brief 原生类型
	QString proTypeName;
	/// @brief 别名列表
	std_vector< QString > aliasTypeName;
	/// @brief 释放函数
	releaseFunction release;
	/// @brief 创建函数
	createFunction create;
	I_Type( ) = delete;
public:
	I_Type( const type_info &type_info )
		: typeInfo( type_info ), proTypeName( type_info.name( ) ) {
		memorySize = 0;
		release = nullptr;
		create = nullptr;
	}
	I_Type( const type_info &type_info, size_t memory_size, const QString &pro_type_name, const std_vector< QString > &alias_type_name, const releaseFunction &release, const createFunction &create )
		: typeInfo( type_info ),
		memorySize( memory_size ),
		proTypeName( pro_type_name ),
		aliasTypeName( alias_type_name ),
		release( release ),
		create( create ) { }
	I_Type( const type_info &type_info, size_t memory_size, const releaseFunction &release, const createFunction &create )
		: typeInfo( type_info ),
		memorySize( memory_size ),
		proTypeName( type_info.name( ) ),
		release( release ), create( create ) { }
	I_Type( const type_info &type_info, const releaseFunction &release, const createFunction &create )
		: typeInfo( type_info ),
		release( release ), proTypeName( type_info.name( ) ),
		create( create ) { }
	friend bool operator==( const I_Type &lhs, const I_Type &rhs ) {
		return lhs.typeInfo == rhs.typeInfo
			&& lhs.memorySize == rhs.memorySize;
	}
	friend bool operator!=( const I_Type &lhs, const I_Type &rhs ) { return !( lhs == rhs ); }
	virtual const QString & getProTypeName( ) const { return proTypeName; }
	virtual const std_vector< QString > & getAliasTypeName( ) const { return aliasTypeName; }
	virtual ~I_Type( ) { }
	/// @brief 获取对象类型
	/// @return 类型信息引用
	virtual const type_info & getTypeInfo( ) const { return typeInfo; }
	/// @brief 获取内存占用大小
	/// @return 创建类型占用大小
	virtual size_t getMemorySize( ) const { return memorySize; }
	/// @brief 设置创建类型占用大小
	/// @param memory_size 类型占用大小
	virtual void setMemorySize( const size_t memory_size ) { memorySize = memory_size; }
	/// @brief 获取释放函数，可用于释放创建指针对象
	/// @return 释放函数
	virtual const releaseFunction & getRelease( ) const { return release; }
	/// @brief 获取创建函数，可用于创建对象
	/// @return 创建函数
	virtual const createFunction & getCreate( ) const { return create; }

	// 静态
public:
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_int8_t( const type_info &info ) {
		return typeid( int8_t ) == info;
	}
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_int16_t( const type_info &info ) {
		return typeid( int16_t ) == info;
	}
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_int32_t( const type_info &info ) {
		return typeid( int32_t ) == info;
	}
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_int64_t( const type_info &info ) {
		return typeid( int64_t ) == info;
	}

	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_uint8_t( const type_info &info ) {
		return typeid( uint8_t ) == info;
	}
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_uint16_t( const type_info &info ) {
		return typeid( uint16_t ) == info;
	}
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_uint32_t( const type_info &info ) {
		return typeid( uint32_t ) == info;
	}
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_uint64_t( const type_info &info ) {
		return typeid( uint64_t ) == info;
	}

	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_float32_t( const type_info &info ) {
		return typeid( float_t ) == info;
	}
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_float64_t( const type_info &info ) {
		return typeid( double_t ) == info;
	}

	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_std_string_t( const type_info &info ) {
		return typeid( std::string ) == info;
	}
	/// @brief 检查是否 int8_t 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_std_wstring_t( const type_info &info ) {
		return typeid( std::wstring ) == info;
	}
	/// @brief 检查是否 QString 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool is_qstring_t( const type_info &info ) {
		return typeid( QString ) == info;
	}

	/// @brief 检查是否 有符号整数 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool isInt( const type_info &info ) {
		if( is_int8_t( info ) || is_int16_t( info ) || is_int32_t( info ) || is_int64_t( info ) )
			return true;
		return false;
	}
	/// @brief 检查是否 无符号整数 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool isUInt( const type_info &info ) {
		if( is_uint8_t( info ) || is_uint16_t( info ) || is_uint32_t( info ) || is_uint64_t( info ) )
			return true;
		return false;
	}
	/// @brief 检查是否 浮点 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool isFloat( const type_info &info ) {
		if( is_float32_t( info ) || is_float64_t( info ) )
			return true;
		return false;
	}
	/// @brief 检查是否 字符串 类型
	/// @param info 检测对象
	/// @return 匹配则返回 true
	static bool isString( const type_info &info ) {
		if( is_std_string_t( info ) || is_std_wstring_t( info ) || is_qstring_t( info ) )
			return true;
		return false;
	}
};
class I_Type_Using_Type_Name {
	friend class VarGenerate;
	static void setInstanceTypeName( I_Type *i_type_ptr, const QString &new_type_name ) {
		i_type_ptr->proTypeName = new_type_name;
	}
	static void setInstanceTypeAliasName( I_Type *i_type_ptr, const std_vector< QString > &new_type_name ) {
		i_type_ptr->aliasTypeName = new_type_name;
	}
	static void setInstanceTypeCreateFunction( I_Type *i_type_ptr, const createFunction &create_function ) {
		i_type_ptr->create = create_function;
	}
	static void setInstanceTypeReleaseFunction( I_Type *i_type_ptr, const releaseFunction &release_function ) {
		i_type_ptr->release = release_function;
	}
	static void setInstanceTypeMemoySize( I_Type *i_type_ptr, const size_t &create_obj_memory_size ) {
		i_type_ptr->memorySize = create_obj_memory_size;
	}
};
#endif // I_TYPE_H_H_HEAD__FILE__
