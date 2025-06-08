#ifndef INODESTACK_H_H_HEAD__FILE__
#define INODESTACK_H_H_HEAD__FILE__
#pragma once
#include "qt/node/nodeWidget/INodeWidget.h"
#include "qt/type/ITypeObject.h"

class INodeStack : public QObject {
	Q_OBJECT;
protected:
	std_vector< std_pairt< INodeWidget *, QString > > storageNode;
public:
	~INodeStack() override;
public:
	/// @brief 生成类型
	/// @param type_name 类型名称
	/// @return 不存在匹配类型返回 nullptr
	virtual INodeWidget * generateNode( const QString &type_name, QWidget *parnet = nullptr ) const = 0;
	/// @brief 存储类型，如果已经存在变量的名称，则返回该对象，并且使用新的覆盖对象
	/// @param storage_obj 存储的对象
	/// @param storage_name 存储的名称
	/// @return 被覆盖的对象
	virtual INodeWidget * setStorageNode( INodeWidget *storage_obj, const QString &storage_name );
	/// @brief 获取存储的对象
	/// @param storage_name 存储的对象名称 
	/// @return 失败返回 nullptr
	virtual INodeWidget * getStorageNode( const QString &storage_name ) const;
	/// @brief 从存储当中删除匹配的变量名
	/// @param storage_name 存储的变量名
	/// @return 被删除的对象，失败返回 nullptr
	virtual INodeWidget * removeStorageNode( const QString &storage_name );
	/// @brief 获取允许生成列表
	/// @return 类名，别名列表
	virtual std_vector< std_pairt< QString, std_vector< QString > > > permissionNodeType( ) const = 0;
protected:
	/// @brief 存储所有已经诞生的存储
	static std_vector< std_shared_ptr< INodeStack > > instanceVector;
public:
	/// @brief 获取类型实例
	/// @tparam TChild_Type 类型
	/// @return 成功返回类型的实例
	template< class TChild_Type >
		requires requires ( TChild_Type *a, INodeStack *te ) {
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
		instanceVector.emplace_back( std_shared_ptr< INodeStack >( result ) );
		return result;
	}
	/// @brief 生成不安全变量
	/// @param type_name 变量类型名称
	/// @param parnet qt 内存管理对象
	/// @return 失败返回 nullptr
	virtual INodeWidget * generateUbNode( const QString &type_name, QWidget *parnet = nullptr ) const {
		INodeWidget *typeObject = generateNode( type_name, parnet );
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
	/// @return 失败返回 nullptr，成功返回自动释放内存变量引用指针对象
	template< class TChild_Type >
		requires requires ( TChild_Type *a, INodeStack *te ) {
			TChild_Type::staticMetaObject.className( );
			te = a;
		}
	static std_shared_ptr< INodeStack > deleteInstance( ) {
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

	/// @brief 生成指定变量
	/// @tparam TChild_Type 变量类型
	/// @param parnet qt 内存管理对象
	/// @return 失败返回 nullptr
	template< class TChild_Type >
		requires requires ( TChild_Type *ta, INodeWidget *cheack ) {
			TChild_Type::staticMetaObject.className( );
			qobject_cast< TChild_Type * >( ta ) ;
			cheack = ta;
		}
	TChild_Type * generateTUBNode( QObject *parnet = nullptr ) const {
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
		requires requires ( TChild_Type *ta, INodeWidget *cheack ) {
			TChild_Type::staticMetaObject.className( );
			qobject_cast< TChild_Type * >( ta ) ;
			cheack = ta;
		}
	TChild_Type * generateTUBNode( const QString &type_name, INodeWidget *parnet = nullptr ) const {
		INodeWidget *typeObject = generateNode( type_name, parnet );
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
	INodeWidget * generateTUBNode( INodeWidget *parnet = nullptr ) const {
		INodeWidget *typeObject = generateNode( QString::fromStdString( type_name ), parnet );
		if( typeObject && parnet )
			typeObject->setParent( parnet );
		return typeObject;
	}
};

#endif // INODESTACK_H_H_HEAD__FILE__
