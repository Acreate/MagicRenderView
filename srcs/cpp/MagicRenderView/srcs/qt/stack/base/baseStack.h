#ifndef BASESTACK_H_H_HEAD__FILE__
#define BASESTACK_H_H_HEAD__FILE__
#pragma once
#include "qt/stack/IVarStack.h"
#include "qt/stack/varInfo/varInfo.h"

class BaseStack : public IVarStack {
	Q_OBJECT;
public:
	friend class IVarStack;
protected:
	/// @brief 生成信息对象列表
	std_vector< std_pairt< std_pairt< QString, QString >, std_function< std_shared_ptr< ITypeObject >( ) > > > generateInfos;
	/// @brief 仓库存储
	std_vector_pairt< std_shared_ptr< ITypeObject >, QString > storage;
protected:
	BaseStack( );
public:
	std_shared_ptr< ITypeObject > generateVar( const QString &type_name ) const override;
	std_shared_ptr< ITypeObject > setStorageVar( const std_shared_ptr< ITypeObject > &storage_obj, const QString &storage_name ) override;
	std_shared_ptr< ITypeObject > getStorageVar( const QString &storage_name ) const override;
	std_shared_ptr< ITypeObject > removeStorageVar( const QString &storage_name )  override;
};

#endif // BASESTACK_H_H_HEAD__FILE__
