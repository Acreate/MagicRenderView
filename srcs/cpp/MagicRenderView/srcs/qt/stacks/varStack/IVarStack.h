#ifndef IVARSTACK_H_H_HEAD__FILE__
#define IVARSTACK_H_H_HEAD__FILE__
#pragma once

#include <QObject>

#include "alias/type_alias.h"

#include "qt/types/ITypeObject.h"
class ITypeObject;
class IVarStack : public QObject {
	Q_OBJECT;
protected:
	/// @brief 仓库存储
	std_shared_ptr< std_vector_pairt< std_shared_ptr< ITypeObject >, QString > > storage;
	std_vector< QString > stackTypeNames;
	std_function< std_shared_ptr< IVarStack >( ) > getStackFunction;
public:
	IVarStack( const std_function< std_shared_ptr< IVarStack >( ) > &get_stack_function_get_function, QObject *parent ) : QObject( parent ), getStackFunction( get_stack_function_get_function ), storage( new std_vector_pairt< std_shared_ptr< ITypeObject >, QString > ) {

	}
public:
	virtual const std_function< std_shared_ptr< IVarStack >( ) > & getGetStackFunction( ) const { return getStackFunction; }
	virtual std_vector< QString > getStackTypeNames( ) const {
		return stackTypeNames;
	}
	/// @brief 存储类型，如果已经存在变量的名称，则返回该对象，并且使用新的覆盖对象
	/// @param storage_obj 存储的对象
	/// @param storage_name 存储的名称
	/// @return 被覆盖的对象
	virtual std_shared_ptr< ITypeObject > setStorageVar( const std_shared_ptr< ITypeObject > &storage_obj, const QString &storage_name ) const;
	/// @brief 获取存储的对象
	/// @param storage_name 存储的对象名称 
	/// @return 失败返回 nullptr
	virtual std_shared_ptr< ITypeObject > getStorageVar( const QString &storage_name ) const;
	/// @brief 从存储当中删除匹配的变量名
	/// @param storage_name 存储的变量名
	/// @return 被删除的对象，失败返回 nullptr
	virtual std_shared_ptr< ITypeObject > removeStorageVar( const QString &storage_name );
public:
	/// @brief 生成类型
	/// @param type_name 类型名称
	/// @return 不存在匹配类型返回 nullptr
	virtual std_shared_ptr< ITypeObject > generateVar( const QString &type_name ) const = 0;
	/// @brief 获取允许生成列表
	/// @return 类名，别名列表
	virtual std_vector< std_pairt< QString, std_vector< QString > > > permissionVarType( ) const = 0;
protected:
	/// @brief 创建非安全指针，需要用户自动释放
	/// @param type_name 类型名称
	/// @return 非安全指针对象
	virtual ITypeObject * _generateUBVar( const QString &type_name ) const = 0;
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
	static std_shared_ptr< TChild_Type > getTUBPtrInstance( ) {
		TChild_Type *child = new TChild_Type( [] { return IVarStack::getInstance< TChild_Type >( ); }, nullptr );
		std_shared_ptr< TChild_Type > result( child );
		return result;
	}
	/// @brief 获取类型实例
	/// @tparam TChild_Type 类型
	/// @return 成功返回类型的实例
	template< class TChild_Type >
		requires requires ( TChild_Type *a, IVarStack *te ) {
			TChild_Type::staticMetaObject.className( );
			te = a;
		}
	static std_shared_ptr< IVarStack > getInstance( ) {
		QString egName = TChild_Type::staticMetaObject.className( );
		for( auto ptr : instanceVector )
			if( ptr->metaObject( )->className( ) == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
				return ptr;
			else
				for( auto &typeName : ptr->getStackTypeNames( ) )
					if( typeName == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
						return ptr;
		std_shared_ptr< IVarStack > result( new TChild_Type( [] { return IVarStack::getInstance< TChild_Type >( ); }, nullptr ) );
		instanceVector.emplace_back( result );
		return result;
	}
	/// @brief 追加一个创建对象。\n
	/// 使用 @code metaObject( )->className( ) @endcode 进行类型名称匹配，如果已经存在重复的类型名称，那么存储失败
	/// @param append_unity 追加的对象指针
	/// @return 成功返回 true
	static bool appendInstance( const std_shared_ptr< IVarStack > &append_unity );
	/// @brief 使用生成器名称获取生成器实例对象
	/// @param stack_name 生成器名称
	/// @return 失败返回 nullptr
	static std_shared_ptr< IVarStack > getInstance( const QString &stack_name );

	/// @brief 生成不安全变量
	/// @param type_name 变量类型名称
	/// @param parnet qt 内存管理对象
	/// @return 失败返回 nullptr
	virtual ITypeObject * generateUbVar( const QString &type_name, QObject *parnet = nullptr ) const;

	/// @brief 释放类型实例
	/// @tparam TChild_Type 类型
	/// @return 失败返回 nullptr，成功返回自动释放内存变量引用指针对象
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
	/// @brief 生成指定类型变量
	/// @tparam TChild_Type 类型
	/// @return 失败返回 nullptr，成功返回自动释放内存变量引用指针对象
	template< class TChild_Type >
		requires requires ( TChild_Type *ta, ITypeObject *cheack ) {
			TChild_Type::staticMetaObject.className( );
			qobject_cast< TChild_Type * >( ta ) ;
			cheack = ta;
		}
	std_shared_ptr< TChild_Type > generateTVar( ) const {
		ITypeObject *typeObject = _generateUBVar( TChild_Type::staticMetaObject.className( ) );
		if( typeObject )
			if( qobject_cast< TChild_Type * >( typeObject ) )
				return std_shared_ptr< TChild_Type >( ( TChild_Type * ) typeObject );
			else
				delete typeObject;
		return nullptr;
	}
	/// @brief 生成变量
	/// @tparam TChild_Type 变量类型
	/// @param type_name 类型名称
	/// @return 失败返回 nullptr，成功返回自动释放内存变量引用指针对象
	template< class TChild_Type >
		requires requires ( TChild_Type *ta, ITypeObject *cheack ) {
			TChild_Type::staticMetaObject.className( );
			qobject_cast< TChild_Type * >( ta ) ;
			cheack = ta;
		}
	std_shared_ptr< TChild_Type > generateTVar( const QString &type_name ) const {
		ITypeObject *typeObject = _generateUBVar( type_name );
		if( typeObject )
			if( qobject_cast< TChild_Type * >( typeObject ) )
				return std_shared_ptr< TChild_Type >( ( TChild_Type * ) typeObject );
			else
				delete typeObject;
		return nullptr;
	}

	/// @brief 生成指定变量
	/// @tparam TChild_Type 变量类型
	/// @param parnet qt 内存管理对象
	/// @return 失败返回 nullptr
	template< class TChild_Type >
		requires requires ( TChild_Type *ta, ITypeObject *cheack ) {
			TChild_Type::staticMetaObject.className( );
			qobject_cast< TChild_Type * >( ta ) ;
			cheack = ta;
		}
	TChild_Type * generateTUBVar( QObject *parnet = nullptr ) const {
		ITypeObject *typeObject = _generateUBVar( TChild_Type::staticMetaObject.className( ) );
		if( typeObject )
			if( qobject_cast< TChild_Type * >( typeObject ) ) {
				typeObject->setParent( parnet );
				return ( TChild_Type * ) typeObject;
			} else
				delete typeObject;

		return nullptr;
	}

	/// @brief 生成指定变量
	/// @tparam TChild_Type 类型
	/// @param type_name 变量名称
	/// @param parnet qt 内存管理对象
	/// @return 失败返回 nullptr
	template< class TChild_Type >
		requires requires ( TChild_Type *ta, ITypeObject *cheack ) {
			TChild_Type::staticMetaObject.className( );
			qobject_cast< TChild_Type * >( ta ) ;
			cheack = ta;
		}
	TChild_Type * generateTUBVar( const QString &type_name, QObject *parnet = nullptr ) const {
		ITypeObject *typeObject = _generateUBVar( type_name );
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
		ITypeObject *typeObject = _generateUBVar( QString::fromStdString( type_name ) );
		if( typeObject && parnet )
			typeObject->setParent( parnet );
		return typeObject;
	}
	
	template< typename IType >
		requires requires ( ITypeObject *c, IType *b ) {
			c = b;
		}
	std_shared_ptr< IType > appendStorageVar( const QString &var_name ) {
		ITypeObject *obj = _generateUBVar( IType::staticMetaObject.className( ) );
		if( obj == nullptr )
			return nullptr;
		std_shared_ptr< IType > newType( ( IType * ) obj );
		setStorageVar( newType, var_name );
		return newType;
	}
};

#endif // IVARSTACK_H_H_HEAD__FILE__
