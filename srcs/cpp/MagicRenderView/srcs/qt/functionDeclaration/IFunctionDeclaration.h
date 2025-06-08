#ifndef IFUNCTIONDECLARATION_H_H_HEAD__FILE__
#define IFUNCTIONDECLARATION_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

class IFunctionDeclaration {
protected:
	/// @brief 变量名称
	std_vector< std_shared_ptr< std_pairt< QString, QString > > > paramInfo;
	/// @brief 变量类型
	QString returnType;
	/// @brief 函数名称
	QString declarationName;
	/// @brief 函数原型
	QString functionDeclarationName;
	/// @brief 属性
	QString attribute;
	/// @brief 是否有效
	bool isValid;
	/// @brief 调换函数
	std_function< void( ) > callFcuntion;
protected:
	/// @brief 使用声明初始化函数信息
	bool init( const QString &function_declaration_name );
	IFunctionDeclaration( ) { }
public:
	IFunctionDeclaration( const QString &function_declaration_name, const std_function< void( ) > &call_function );

	IFunctionDeclaration( const IFunctionDeclaration &other )
		: paramInfo( other.paramInfo ),
		returnType( other.returnType ),
		declarationName( other.declarationName ),
		functionDeclarationName( other.functionDeclarationName ),
		attribute( other.attribute ),
		isValid( other.isValid ),
		callFcuntion( other.callFcuntion ) { }
	IFunctionDeclaration & operator=( const IFunctionDeclaration &other ) {
		if( this == &other )
			return *this;
		paramInfo = other.paramInfo;
		returnType = other.returnType;
		declarationName = other.declarationName;
		functionDeclarationName = other.functionDeclarationName;
		attribute = other.attribute;
		isValid = other.isValid;
		callFcuntion = other.callFcuntion;
		return *this;
	}
	virtual ~IFunctionDeclaration( ) { }
	/// @brief 调用一次函数
	virtual void call( ) const {
		if( callFcuntion )
			callFcuntion( );
	}
	/// @brief 获取调用函数
	/// @return 调用函数
	virtual std_function< void( ) > getFunction( ) const {
		return callFcuntion;
	}
	virtual const std_vector< std_shared_ptr< std_pairt< QString, QString > > > & getParamInfos( ) const { return paramInfo; }
	/// @brief 获取参数个数
	/// @return 参数数量
	virtual size_t getParamCount( ) const {
		return paramInfo.size( );
	}
	/// @brief 获取指定参数名称的下标
	/// @param param_name 参数名称
	/// @param result_index 返回下标，失败返回参数个数
	/// @return 成功返回 true。不存在该名称，返回 false
	virtual bool getNameParamIndex( const QString &param_name, size_t &result_index ) const {
		size_t count = paramInfo.size( );
		auto data = paramInfo.data( );
		for( result_index = 0; result_index < count; ++result_index )
			if( param_name == data[ result_index ]->second )
				return true;
		return false;
	}

	/// @brief 获取名称类型，失败返回空
	/// @param param_name 
	/// @return 参数名称匹配的类型
	virtual QString getNameParamTypeInfo( const QString &param_name ) const {
		for( auto itemSharedPtr : paramInfo )
			if( itemSharedPtr->second == param_name )
				return itemSharedPtr->first;
		return "";
	}
	/// @brief 获取参数下标匹配的项
	/// @param index 下标
	/// @return 项，类型与之匹配的名称-名称可能为空
	std_shared_ptr< std_pairt< QString, QString > > getParamInfo( const size_t &index ) const {
		size_t count = paramInfo.size( );
		if( count > index )
			return paramInfo[ index ];
		return nullptr;
	}
	virtual const QString & getReturnType( ) const { return returnType; }
	virtual const QString & getDeclarationName( ) const { return declarationName; }
	virtual const QString & getAttribute( ) const { return attribute; }
	virtual const QString & getFunctionDeclarationName( ) const { return functionDeclarationName; }
	/// @brief 是否有效
	/// @return 返回 false 表示无效声明
	virtual bool isIsValid( ) const { return isValid; }
};

#endif // IFUNCTIONDECLARATION_H_H_HEAD__FILE__
