#ifndef BASESTACK_H_H_HEAD__FILE__
#define BASESTACK_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

#include "qt/types/ITypeObject.h"
#include "../IVarStack.h"
/// @brief 使用 IVarStack::getInstance< BaseStack >( ); 创建该实例
class BaseVarStack : public IVarStack {
	Q_OBJECT;
public:
	friend class IVarStack;
protected:
	/// @brief 生成信息对象列表
	std_vector< std_pairt< std_pairt< QString, std_vector< QString > >, std_function< ITypeObject *( ) > > > generateInfos;
public:
	BaseVarStack( const std_function< std_shared_ptr< IVarStack >( ) > &get_stack_function_get_function = nullptr, QObject *parent = nullptr );
protected:
	ITypeObject * newVar( const QString &type_name ) const;
	ITypeObject * _generateUBVar( const QString &type_name ) const override;
	/// @brief 生成信息对象列表去重
	void generateInfosRemoveRe( );
public:
	std_shared_ptr< ITypeObject > generateVar( const QString &type_name ) const override;
	std_vector< std_pairt< QString, std_vector< QString > > > permissionVarType( ) const override;
};

#endif // BASESTACK_H_H_HEAD__FILE__
