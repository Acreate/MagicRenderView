#ifndef INODESTACK_H_H_HEAD__FILE__
#define INODESTACK_H_H_HEAD__FILE__
#pragma once
#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/node/nodeWidget/INodeWidget.h"
#include "qt/type/ITypeObject.h"

class NodeAddMenu;
class INodeStack : public QObject {
	Q_OBJECT;
protected:
	std_shared_ptr<INodeStack> INodeStackThis;
	std_vector< QString > stackTypeNames;
	std_function< std_shared_ptr< INodeStack >( ) > getStackFunction;
public:
	INodeStack( const std_function< std_shared_ptr< INodeStack >( ) > &get_stack_function );
	~INodeStack( ) override;
	const std_vector< QString > & getStackTypeNames( ) const { return stackTypeNames; }
	const std_function< std_shared_ptr< INodeStack >( ) > & getGetStackFunction( ) const { return getStackFunction; }
public:
	/// @brief 生成类型
	/// @param type_name 类型名称
	/// @param parnet 可挂载的父对象
	/// @return 不存在匹配类型返回 nullptr
	virtual INodeWidget * generateNode( const QString &type_name, QWidget *parnet = nullptr ) const = 0;
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
	static std_shared_ptr< INodeStack > getStdSharedPtrInstance( ) {
		QString egName = TChild_Type::staticMetaObject.className( );
		std_shared_ptr< INodeStack > result;
		for( auto &ptr : instanceVector )
			if( ptr->metaObject( )->className( ) == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
				return ptr;
			else
				for( auto &name : ptr->getStackTypeNames( ) )
					if( name == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
						return ptr;

		INodeStack *child = new TChild_Type( [] {
			return INodeStack::getStdSharedPtrInstance< TChild_Type >( );
		} );
		result = std_shared_ptr< INodeStack >( child );
		instanceVector.emplace_back( result );
		return result;
	}

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
		std_shared_ptr< INodeStack > result;
		for( auto &ptr : instanceVector )
			if( ptr->metaObject( )->className( ) == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
				return ( TChild_Type * ) ptr.get( );
			else
				for( auto &name : ptr->getStackTypeNames( ) )
					if( name == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
						return ( TChild_Type * ) ptr.get( );
		TChild_Type *child = new TChild_Type( [] {
			return INodeStack::getStdSharedPtrInstance< TChild_Type >( );
		} );
		result = std_shared_ptr< INodeStack >( child );
		instanceVector.emplace_back( result );
		return child;
	}
	/// @brief 根据名称获取节点工厂的安全指针
	/// @param stack_name 节点工厂名称
	/// @return 失败返回 nullptr
	static std_shared_ptr< INodeStack > getStdSharedPtrInstance( const QString &stack_name );
	/// @brief 追加一个创建对象。\n
	/// 使用 @code metaObject( )->className( ) @endcode 进行类型名称匹配，如果已经存在重复的类型名称，那么存储失败
	/// @param append_unity 追加的对象指针
	/// @return 成功返回 true
	static bool appendInstance( const std_shared_ptr< INodeStack > &append_unity ) {
		auto egName = append_unity->metaObject( )->className( );
		for( auto &ptr : instanceVector )
			if( ptr->metaObject( )->className( ) == egName )
				return false;
		instanceVector.emplace_back( append_unity );
		return true;
	}
	/// @brief 使用生成器名称获取生成器实例对象
	/// @param stack_name 生成器名称
	/// @return 失败返回 nullptr
	static INodeStack * getInstance( const QString &stack_name );
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
			} else
				for( auto &name : iterator.operator*( )->getStackTypeNames( ) )
					if( name == egName ) {
						auto varStack = *iterator;
						instanceVector.erase( iterator );
						return varStack;
					}
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
