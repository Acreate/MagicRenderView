#ifndef I_VAR_H_H_HEAD__FILE__
#define I_VAR_H_H_HEAD__FILE__
#pragma once
#include <alias/type_alias.h>

class I_Type;
class I_Var {
	friend class I_Stack;
protected:
	/// @brief 类型信息
	std_shared_ptr< I_Type > typeInfo;
	/// @brief 生成代码
	size_t generateCode;
	/// @brief 指针
	void *p;
	/// @brief 变量名称
	QString varName;
public:
	I_Var( const std_shared_ptr< I_Type > &type_info, const QString &var_name );
	I_Var( const std_shared_ptr< I_Type > &type_info, const size_t &generate_code, const QString &var_name );
	I_Var( const I_Var &other );
	I_Var & operator=( const I_Var &other );
	virtual ~I_Var( );
	virtual const std_shared_ptr< I_Type > & getTypeInfo( ) const { return typeInfo; }
	virtual void * getP( ) const { return p; }
	virtual const QString & getVarName( ) const { return varName; }
	virtual size_t getGenerateCode( ) const { return generateCode; }
};

#endif // I_VAR_H_H_HEAD__FILE__
