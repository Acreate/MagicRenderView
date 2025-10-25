﻿#ifndef I_VAR_H_H_HEAD__FILE__
#define I_VAR_H_H_HEAD__FILE__
#pragma once
#include <alias/type_alias.h>

class I_Type;
class I_Var {
	friend class I_Stack;
protected:
	/// @brief 类型信息
	I_Type *typeInfo;
	/// @brief 生成代码
	size_t generateCode;
	/// @brief 指针
	void *p;
	/// @brief 变量名称
	QString varName;
public:
	I_Var( I_Type *type_info ) : I_Var( type_info, "" ) { }
	I_Var( I_Type *type_info, const QString &var_name );
	I_Var( I_Type *type_info, const size_t &generate_code, const QString &var_name );
	I_Var( const I_Type &type_info ) : I_Var( type_info, "" ) { }
	I_Var( const I_Type &type_info, const QString &var_name );
	I_Var( const I_Type &type_info, const size_t &generate_code, const QString &var_name );
	I_Var( const I_Var &other );
	I_Var & operator=( const I_Var &other );
	virtual ~I_Var( );
	/// @brief 获取对象存储的类型信息
	/// @return 类型信息对象
	virtual const I_Type * getTypeInfo( ) const { return typeInfo; }
	/// @brief 获取对象存储的指针
	/// @return 指针
	virtual void * getVarPtr( ) const { return p; }
	/// @brief 该功能重置 p 为 nullptr，删除对象时，不再调用释放函数释放指针
	virtual void resetVarPtrToNullptr( ) { p = nullptr; }
	/// @brief 获取对象名称
	/// @return 对象名称
	virtual const QString & getVarName( ) const { return varName; }
	/// @brief 设置对象名称
	/// @param var_name 新的对象名称
	virtual void setVarName( const QString &var_name ) { varName = var_name; }
	/// @brief 获取生成代码
	/// @return 生成代码
	virtual size_t getGenerateCode( ) const { return generateCode; }
protected:
	static I_Type * generateType( const type_info &type_info, size_t memory_size, const QString &pro_type_name, const std_vector< QString > &alias_type_name, const releaseFunction &release, const createFunction &create );
public:
	template< typename TGenerateType >
	static I_Var * generateVarPtr( const QString &pro_type_name, const std_vector< QString > &alias_type_name, const releaseFunction &release, const createFunction &create ) {
		auto type = generateType( typeid( TGenerateType ), sizeof( TGenerateType ), pro_type_name, alias_type_name, release, create );
		return new I_Var( type );
	}

	template< typename TGenerateType >
	static I_Var * generateVarPtr( const releaseFunction &release, const createFunction &create ) {
		return generateVarPtr< TGenerateType >( "", { }, release, create );
	}

	template< typename TGenerateType >
	static I_Var * generateVarPtr( const QString &pro_type_name, const std_vector< QString > &alias_type_name ) {
		auto release = [] ( void *p ) {
			delete ( TGenerateType * ) p;
			return true;
		};
		auto create = [] {
			return new TGenerateType( 0 );
		};
		return generateVarPtr< TGenerateType >( pro_type_name, alias_type_name, release, create );
	}
	template< typename TGenerateType >
	static I_Var * generateVarPtr( ) {
		auto release = [] ( void *p ) {
			delete ( TGenerateType * ) p;
			return true;
		};
		auto create = [] {
			return new TGenerateType( 0 );
		};
		return generateVarPtr< TGenerateType >( "", { }, release, create );
	}
};

#endif // I_VAR_H_H_HEAD__FILE__
