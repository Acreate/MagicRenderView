#ifndef IFUNCTIONDECLARATION_H_H_HEAD__FILE__
#define IFUNCTIONDECLARATION_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include "qt/serialize/ISerialize.h"
#include "qt/types/ITypeObject.h"
class INodeWidget;
class StringTypeObject;
class IFunctionDeclaration : public QObject {
	Q_OBJECT;
public:
	using std_call = std_function< std_shared_ptr< ITypeObject >( const IVarStack &, IVarStack &, const IFunctionDeclaration & ) >;
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
	std_call callFcuntion;
	/// @brief 函数说明
	QImage *image = nullptr;
	/// @brief 是否代表控制代码
	bool isControlCode;
protected:
	/// @brief 使用声明初始化函数信息
	bool _init( const QString &function_declaration_name );
public:
	IFunctionDeclaration( const QString &function_declaration_name, const std_call &call_function );
	virtual bool isIsControlCode( ) const { return isControlCode; }
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
	/// @brief 使用声明初始化函数信息
	virtual bool initDeclaration( const QString &function_declaration_name ) {
		return _init( function_declaration_name );
	}
	const std_call & getCallFcuntion( ) const { return callFcuntion; }
	void setCallFcuntion( const std_call &call_fcuntion ) { callFcuntion = call_fcuntion; }
	/// @brief 获取调用函数
	/// @return 调用函数
	virtual std_call getFunction( ) const {
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
	/// @brief 获取返回类型
	virtual const QString & getReturnType( ) const { return returnType; }
	/// @brief 获取返回值变量的名称
	/// @return 返回值变量的名称
	virtual QString getReturnValueName( ) const {
		return functionDeclarationName + ".result";
	}
	/// @brief 获取函数名称
	virtual const QString & getDeclarationName( ) const { return declarationName; }
	/// @brief 获取属性
	virtual const QString & getAttribute( ) const { return attribute; }
	/// @brief 获取函数原型
	virtual const QString & getFunctionDeclarationName( ) const { return functionDeclarationName; }
	/// @brief 是否有效
	/// @return 返回 false 表示无效声明
	virtual bool isIsValid( ) const { return isValid; }
	/// @brief 获取函数说明
	/// @return 图型显示图片
	virtual QImage * getImage( ) const { return image; }
};

#endif // IFUNCTIONDECLARATION_H_H_HEAD__FILE__
