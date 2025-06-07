#ifndef BASESTACK_H_H_HEAD__FILE__
#define BASESTACK_H_H_HEAD__FILE__
#pragma once
#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"
#include "../IVarStack.h"
/// @brief 使用 IVarStack::getInstance< BaseStack >( ); 创建该实例
class BaseStack : public IVarStack {
	Q_OBJECT;
public:
	friend class IVarStack;
protected:
	/// @brief 生成信息对象列表
	std_vector< std_pairt< std_pairt< QString, std_vector< QString > >, std_function< ITypeObject *( ) > > > generateInfos;
	/// @brief 仓库存储
	std_vector_pairt< std_shared_ptr< ITypeObject >, QString > storage;
protected:
	BaseStack( QObject *parent = nullptr );
	ITypeObject * newVar( const QString &type_name ) const;
	ITypeObject * _generateUBVar( const QString &type_name ) const override;
public:
	std_shared_ptr< ITypeObject > generateVar( const QString &type_name ) const override;
	std_shared_ptr< ITypeObject > setStorageVar( const std_shared_ptr< ITypeObject > &storage_obj, const QString &storage_name ) override;
	std_shared_ptr< ITypeObject > getStorageVar( const QString &storage_name ) const override;
	std_shared_ptr< ITypeObject > removeStorageVar( const QString &storage_name ) override;
	std_vector< std_pairt< QString, std_vector< QString > > > permissionVarType( ) const override;
};

#endif // BASESTACK_H_H_HEAD__FILE__
