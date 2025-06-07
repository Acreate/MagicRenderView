#ifndef IVARSTACK_H_H_HEAD__FILE__
#define IVARSTACK_H_H_HEAD__FILE__
#pragma once

#include <QObject>

#include "alias/type_alias.h"

#include "qt/type/ITypeObject.h"
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
	/// @brief 创建非安全指针，需要用户自动释放
	/// @param type_name 类型名称
	/// @return 非安全指针对象
	virtual ITypeObject * generateUBVar( const QString &type_name ) const = 0;
protected:
	/// @brief 存储所有已经诞生的存储
	static std_vector< std_shared_ptr< IVarStack > > instanceVector;
public:
	/// @brief 获取类型实例
	/// @tparam TChild_Type 类型
	/// @return 成功返回类型的实例
	template< class TChild_Type >
		requires requires ( TChild_Type *a, IVarStack *te ) {
			TChild_Type::staticMetaObject.className( );
			te = a;
		}
	static TChild_Type * getInstance( ) {
		QString egName = TChild_Type::staticMetaObject.className( );
		TChild_Type *result;
		for( auto &ptr : instanceVector )
			if( ptr->metaObject( )->className( ) == egName ) {
				result = qobject_cast< TChild_Type * >( ptr.get( ) );
				if( result )
					return result;
			}
		result = new TChild_Type( );
		instanceVector.emplace_back( std_shared_ptr< IVarStack >( result ) );
		return result;
	}

	virtual ITypeObject * generateNewVar( const QString &type_name, QObject *parnet = nullptr ) const {
		ITypeObject *typeObject = generateUBVar( type_name );
		if( typeObject )
			if( parnet ) {
				typeObject->setParent( parnet );
				return typeObject;
			} else
				return typeObject;
		return nullptr;
	}

	/// @brief 释放类型实例
	/// @tparam TChild_Type 类型
	/// @return 成功返回释放实例对象引用
	template< class TChild_Type >
		requires requires ( TChild_Type *a, IVarStack *te ) {
			TChild_Type::staticMetaObject.className( );
			te = a;
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

	template< class TChild_Type >
		requires requires ( TChild_Type *ta, ITypeObject *cheack ) {
			TChild_Type::staticMetaObject.className( );
			qobject_cast< TChild_Type * >( ta ) ;
			cheack = ta;
		}
	std_shared_ptr< TChild_Type > generateTVar( ) const {
		ITypeObject *typeObject = generateUBVar( TChild_Type::staticMetaObject.className( ) );
		if( typeObject )
			if( qobject_cast< TChild_Type * >( typeObject ) )
				return std_shared_ptr< TChild_Type >( ( TChild_Type * ) typeObject );
			else
				delete typeObject;
		return nullptr;
	}

	template< class TChild_Type >
		requires requires ( TChild_Type *ta, ITypeObject *cheack ) {
			TChild_Type::staticMetaObject.className( );
			qobject_cast< TChild_Type * >( ta ) ;
			cheack = ta;
		}
	TChild_Type * generateTUBVar( QObject *parnet = nullptr ) const {
		ITypeObject *typeObject = generateUBVar( TChild_Type::staticMetaObject.className( ) );
		if( typeObject )
			if( qobject_cast< TChild_Type * >( typeObject ) ) {
				typeObject->setParent( parnet );
				return ( TChild_Type * ) typeObject;
			} else
				delete typeObject;

		return nullptr;
	}

	/// @brief 	static const char hello17[ ] = "Hello World!"; // no linkage
	/// @brief 	使用字符串进行变量生成-该方式不会诞生共享释放的变量对象
	/// @tparam type_name 变量名称
	/// @param parnet 父对象
	/// @return 成功返回非 nullptr
	template< const char * type_name >
	ITypeObject * generateTUBVar( QObject *parnet = nullptr ) const {
		ITypeObject *typeObject = generateUBVar( QString::fromStdString( type_name ) );
		if( typeObject && parnet )
			typeObject->setParent( parnet );
		return typeObject;
	}
};

#endif // IVARSTACK_H_H_HEAD__FILE__
