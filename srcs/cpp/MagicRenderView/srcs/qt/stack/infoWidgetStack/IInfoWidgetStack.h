#ifndef IINFOWIDGETSTACK_H_H_HEAD__FILE__
#define IINFOWIDGETSTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

class IInfoWidget;
class IInfoWidgetStack : public QObject {
	Q_OBJECT;
protected:
	std_vector< std_pairt< IInfoWidgetStack *, QString > > storageNode;
	std_vector< QString > stackTypeNames;
	std_function< std_shared_ptr< IInfoWidgetStack >( ) > getStackFunction;
public:
	IInfoWidgetStack( const std_function< std_shared_ptr< IInfoWidgetStack >( ) > &get_stack_function )
		: getStackFunction( get_stack_function ) { }
	const std_vector< QString > & getStackTypeNames( ) const { return stackTypeNames; }
	const std_function< std_shared_ptr< IInfoWidgetStack >( ) > & getGetStackFunction( ) const { return getStackFunction; }
	/// @brief 生成类型
	/// @param type_name 类型名称
	/// @param parnet 可挂载的父对象
	/// @return 不存在匹配类型返回 nullptr
	virtual IInfoWidget * generateNode( const QString &type_name, QWidget *parnet = nullptr ) const = 0;
	/// @brief 获取允许生成列表
	/// @return 类名，别名列表
	virtual std_vector< std_pairt< QString, std_vector< QString > > > permissionInfoWidget( ) const = 0;
public:
	/// @brief 存储所有已经诞生的存储
	static std_vector< std_shared_ptr< IInfoWidgetStack > > instanceVector;
public:
	/// @brief 获取类型实例
	/// @tparam TChild_Type 类型
	/// @return 成功返回类型的实例
	template< class TChild_Type >
		requires requires ( TChild_Type *a, IInfoWidgetStack *te ) {
			TChild_Type::staticMetaObject.className( );
			te = a;
		}
	static std_shared_ptr< IInfoWidgetStack > getStdSharedPtrInstance( ) {
		QString egName = TChild_Type::staticMetaObject.className( );
		std_shared_ptr< IInfoWidgetStack > result;
		for( auto &ptr : instanceVector )
			if( ptr->metaObject( )->className( ) == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
				return ptr;
			else
				for( auto &name : ptr->getStackTypeNames( ) )
					if( name == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
						return ptr;

		IInfoWidgetStack *child = new TChild_Type( [] {
			return IInfoWidgetStack::getStdSharedPtrInstance< TChild_Type >( );
		} );
		result = std_shared_ptr< IInfoWidgetStack >( child );
		instanceVector.emplace_back( result );
		return result;
	}

	/// @brief 获取类型实例
	/// @tparam TChild_Type 类型
	/// @return 成功返回类型的实例
	template< class TChild_Type >
		requires requires ( TChild_Type *a, IInfoWidgetStack *te ) {
			TChild_Type::staticMetaObject.className( );
			te = a;
		}
	static TChild_Type * getInstance( ) {
		QString egName = TChild_Type::staticMetaObject.className( );
		std_shared_ptr< IInfoWidgetStack > result;
		for( auto &ptr : instanceVector )
			if( ptr->metaObject( )->className( ) == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
				return ( TChild_Type * ) ptr.get( );
			else
				for( auto &name : ptr->getStackTypeNames( ) )
					if( name == egName && qobject_cast< TChild_Type * >( ptr.get( ) ) )
						return ( TChild_Type * ) ptr.get( );
		TChild_Type *child = new TChild_Type( [] {
			return IInfoWidgetStack::getStdSharedPtrInstance< TChild_Type >( );
		} );
		result = std_shared_ptr< IInfoWidgetStack >( child );
		instanceVector.emplace_back( result );
		return child;
	}
	/// @brief 根据名称获取节点工厂的安全指针
	/// @param stack_name 节点工厂名称
	/// @return 失败返回 nullptr
	static std_shared_ptr< IInfoWidgetStack > getStdSharedPtrInstance( const QString &stack_name );
	/// @brief 追加一个创建对象。\n
	/// 使用 @code metaObject( )->className( ) @endcode 进行类型名称匹配，如果已经存在重复的类型名称，那么存储失败
	/// @param append_unity 追加的对象指针
	/// @return 成功返回 true
	static bool appendInstance( const std_shared_ptr< IInfoWidgetStack > &append_unity ) {
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
	static IInfoWidgetStack * getInstance( const QString &stack_name );
};

#endif // IINFOWIDGETSTACK_H_H_HEAD__FILE__
