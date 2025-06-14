#ifndef BASESTACKEX_H_H_HEAD__FILE__
#define BASESTACKEX_H_H_HEAD__FILE__
#pragma once
#include "baseVarStack.h"

class BaseVarStackEx : public BaseVarStack {
	Q_OBJECT;
public:
	friend class IVarStack;
protected:
	/// @brief 生成信息对象列表
	std_vector< std_pairt< std_vector< QString >, std_function< ITypeObject *( ) > > > generateInfosEx;
protected:
	BaseVarStackEx( const std_function< std_shared_ptr< IVarStack >( ) > &get_stack_function_get_function, QObject *parent );
	ITypeObject * newVar( const QString &type_name ) const;
	ITypeObject * _generateUBVar( const QString &type_name ) const override;
public:
	std_vector< std_pairt< QString, std_vector< QString > > > permissionVarType( ) const override;
};

#endif // BASESTACKEX_H_H_HEAD__FILE__
