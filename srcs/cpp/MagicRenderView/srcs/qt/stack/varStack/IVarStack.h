#ifndef IVARSTACK_H_H_HEAD__FILE__
#define IVARSTACK_H_H_HEAD__FILE__
#pragma once

#include <QObject>

#include "alias/type_alias.h"
class ITypeObject;
class IVarStack : public QObject {
	Q_OBJECT;
public:
	IVarStack( QObject *parent ) : QObject( parent ) { }
	/// @brief 生成类型
	/// @param type_name 类型名称
	/// @return 不存在匹配类型返回 nullptr
	virtual std_shared_ptr< ITypeObject > generateVar( const QString &type_name ) const = 0;
	/// @brief 存储类型，如果已经存在变量的名称，则返回该对象，并且使用新的覆盖对象
	/// @param storage_obj 存储的对象
	/// @param storage_name 存储的名称
	/// @return 被覆盖的对象
	virtual std_shared_ptr< ITypeObject > setStorageVar( const std_shared_ptr< ITypeObject > &storage_obj, const QString &storage_name ) = 0;
	/// @brief 获取存储的对象
	/// @param storage_name 存储的对象名称 
	/// @return 失败返回 nullptr
	virtual std_shared_ptr< ITypeObject > getStorageVar( const QString &storage_name ) const = 0;
	/// @brief 从存储当中删除匹配的变量名
	/// @param storage_name 存储的变量名
	/// @return 被删除的对象，失败返回 nullptr
	virtual std_shared_ptr< ITypeObject > removeStorageVar( const QString &storage_name ) = 0;
	/// @brief 获取允许生成列表
	/// @return 类名，别名列表
	virtual std_vector< std_pairt< QString, std_vector< QString > > > permissionVarType( ) const = 0;
protected:
	/// @brief 存储所有已经诞生的存储
	static std_vector< std_shared_ptr< IVarStack > > instanceVector;
public:
	/// @brief 获取类型实例
	/// @tparam TChild_Type 类型
	/// @return 成功返回类型的实例
	template< class TChild_Type >
		requires requires {
			TChild_Type::staticMetaObject.className( );
		}
	static std_shared_ptr< IVarStack > getInstance( ) {
		QString egName = TChild_Type::staticMetaObject.className( );
		for( auto &ptr : instanceVector )
			if( ptr->metaObject( )->className( ) == egName )
				return ptr;
		auto result = std_shared_ptr< IVarStack >( new TChild_Type );
		instanceVector.emplace_back( result );
		return result;
	}
	/// @brief 释放类型实例
	/// @tparam TChild_Type 类型
	/// @return 成功返回释放实例对象引用
	template< class TChild_Type >
		requires requires {
			TChild_Type::staticMetaObject.className( );
		}
	static std_shared_ptr< IVarStack > deleteInstance( ) {
		QString egName = TChild_Type::staticMetaObject.className( );
		auto iterator = instanceVector.begin( );
		auto end = instanceVector.end( );
		for( ; iterator != end; ++iterator )
			if( iterator.operator*( )->metaObject( )->className( ) == egName ) {
				auto varStack = *iterator;
				instanceVector.erase( iterator );
				return varStack;
			}

		return nullptr;
	}
};

#endif // IVARSTACK_H_H_HEAD__FILE__
