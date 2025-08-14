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
	QString stackTypeName;
	std_function< std_shared_ptr< IVarStack >( ) > getStackFunction;
public:
	IVarStack( const std_function< std_shared_ptr< IVarStack >( ) > &get_stack_function_get_function, QObject *parent ) : QObject( parent ), storage( new std_vector_pairt< std_shared_ptr< ITypeObject >, QString > ), getStackFunction( get_stack_function_get_function ) {

	}
public:
	virtual const std_function< std_shared_ptr< IVarStack >( ) > & getGetStackFunction( ) const { return getStackFunction; }
	virtual const QString & getStackTypeName( ) const {
		return stackTypeName;
	}
	/// @brief 存储类型，如果已经存在变量的名称，则返回该对象，并且使用新的覆盖对象
	/// @param storage_obj 存储的对象
	/// @param storage_name 存储的名称
	/// @return 被覆盖的对象
	virtual std_shared_ptr< ITypeObject > setStorageVar( const std_shared_ptr< ITypeObject > &storage_obj, const QString &storage_name );
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
public:
	/// @brief 生成不安全变量
	/// @param type_name 变量类型名称
	/// @param parnet qt 内存管理对象
	/// @return 失败返回 nullptr
	virtual ITypeObject * generateUbVar( const QString &type_name, QObject *parnet = nullptr ) const;

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
