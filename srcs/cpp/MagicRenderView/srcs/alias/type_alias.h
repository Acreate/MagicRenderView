#ifndef TYPE_ALIAS_H_H_HEAD__FILE__
#define TYPE_ALIAS_H_H_HEAD__FILE__
#pragma once

#include "cmake_value_to_c_cpp_header_env.h"
#include <vector>
#include <memory>
#include <QString>
#include <set>
#include <QEvent>
#include <mutex>
/// @brief 事件类型
using t_event_type = decltype(QEvent::Type::AcceptDropsChange);

template< typename TPtrType >
using std_shared_ptr = std::shared_ptr< TPtrType >;

/// @brief 映射容器
/// @tparam TKey 映射关键字
/// @tparam TValue 映射值
template< typename TKey, typename TValue >
using std_pairt = std::pair< TKey, TValue >;
/// @brief 映射序列容器
/// @tparam TKey 映射关键字
/// @tparam TValue 映射值
template< typename TKey, typename TValue >
using std_vector_pairt = std::vector< std_pairt< TKey, TValue > >;

/// @brief 容器别名
/// @tparam TValue 元素类型 
template< typename TValue >
using std_vector = std::vector< TValue >;

/// @brief 列表别名
/// @tparam TValue 元素类型 
template< typename TValue >
using std_list = std::list< TValue >;

/// @brief 容器别名
/// @tparam TValue 元素类型 
template< typename TValue >
using std_vector_unity_shared = std::vector< std_shared_ptr< TValue > >;

/// @brief 共享指针容器指针对象
/// @tparam TValue 元素类型 
template< typename TValue >
using std_vector_shared_unity_shared = std_shared_ptr< std_vector_unity_shared< TValue > >;

/// @brief 红黑树别名
/// @tparam TValue 元素类型 
template< typename TValue >
using std_set = std::set< TValue >;
/// @brief 属性功能函数
template< typename TFunction >
using std_function = std::function< TFunction >;
/// @brief 锁
using std_mutex = std::mutex;
/// @brief 自动锁
using std_lock_grad_mutex = std::lock_guard< std_mutex >;

#ifdef Def_First_StaticMetaInfo
#undef Def_First_StaticMetaInfo
#endif

#define Def_First_StaticMetaInfo(  ) \
protected: \
	static QString getStaticMetaObjectName( ); \
	static QString getStaticMetaObjectDir( ); \
public: \
	virtual QString getMetaObjectName( ) const; \
	virtual QString getMetaObjectDir( ) const

#ifdef Def_Last_StaticMetaInfo
#undef Def_Last_StaticMetaInfo
#endif

#define Def_Last_StaticMetaInfo(  ) \
protected: \
	static QString getStaticMetaObjectName( ); \
	static QString getStaticMetaObjectDir( ); \
public: \
	QString getMetaObjectName( ) const override; \
	QString getMetaObjectDir( ) const override

#ifdef Def_Last_Firend_StaticMetaInfo
#undef Def_Last_Firend_StaticMetaInfo
#endif

#define Def_Last_Firend_StaticMetaInfo( Friend_Class ) \
public:\
	friend class Friend_Class;\
protected: \
	static QString getStaticMetaObjectName( ); \
	static QString getStaticMetaObjectDir( ); \
public: \
	QString getMetaObjectName( ) const override; \
	QString getMetaObjectDir( ) const override
#ifdef Imp_StaticMetaInfo
#undef Imp_StaticMetaInfo
#endif

#define Imp_StaticMetaInfo( Imp_Class , Class_Translate,  Dir_Translate) \
	QString Imp_Class::getStaticMetaObjectName( ) { \
		return Class_Translate; \
	} \
	QString Imp_Class::getStaticMetaObjectDir( ) { \
		return Dir_Translate; \
	}\
	QString Imp_Class::getMetaObjectName( ) const {\
		return Class_Translate;\
	}\
	QString Imp_Class::getMetaObjectDir( ) const {\
		return Dir_Translate;\
	}class Imp_Class

class Type_Alias {
	Def_First_StaticMetaInfo( );
public:
	virtual ~Type_Alias( ) { }
};
#endif // TYPE_ALIAS_H_H_HEAD__FILE__
