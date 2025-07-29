#ifndef ITYPEOBJECT_H_H_HEAD__FILE__
#define ITYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include <QObject>

#include "alias/type_alias.h"

#include "qt/serialize/ISerialize.h"

#define operator_virtual_equ( Type, Return_var )\
virtual	operator uint8_t( ) const {\
		return Return_var;\
	}\
virtual	operator uint16_t( ) const {\
		return Return_var;\
	}\
virtual	operator uint32_t( ) const {\
		return Return_var;\
	}\
virtual	operator uint64_t( ) const {\
		return Return_var;\
	}\
virtual	operator int8_t( ) const {\
		return Return_var;\
	}\
virtual	operator int16_t( ) const {\
		return Return_var;\
	}\
virtual	operator int32_t( ) const {\
		return Return_var;\
	}\
virtual	operator int64_t( ) const {\
		return Return_var;\
	}\
virtual	operator float( ) const {\
		return Return_var;\
	}\
virtual	operator double( ) const {\
		return Return_var;\
	}\
virtual	Type & operator=( const int8_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const int16_t &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const int32_t &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const int64_t &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const uint8_t &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const uint16_t &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const uint32_t &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const uint64_t &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const float &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
virtual	Type & operator=( const double &right ) {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}

#define operator_override_equ( Type, Return_var )\
	operator uint8_t( ) const override {\
		return Return_var;\
	}\
	operator uint16_t( ) const override {\
		return Return_var;\
	}\
	operator uint32_t( ) const override {\
		return Return_var;\
	}\
	operator uint64_t( ) const override {\
		return Return_var;\
	}\
	operator int8_t( ) const override {\
		return Return_var;\
	}\
	operator int16_t( ) const override {\
		return Return_var;\
	}\
	operator int32_t( ) const override {\
		return Return_var;\
	}\
	operator int64_t( ) const override {\
		return Return_var;\
	}\
	operator float( ) const override {\
		return Return_var;\
	}\
	operator double( ) const override {\
		return Return_var;\
	}\
	Type & operator=( const int8_t &right ) override {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const int16_t &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
	Type & operator=( const int32_t &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
	Type & operator=( const int64_t &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
	Type & operator=( const uint8_t &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
	Type & operator=( const uint16_t &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
	Type & operator=( const uint32_t &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
	Type & operator=( const uint64_t &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
	Type & operator=( const float &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}\
	Type & operator=( const double &right ) override {\
		if(this != nullptr) \
			Return_var = right;\
		return *this;\
	}

#define Def_Clone_Move_override_function(type_)\
	type_( const ITypeObject &other ) {\
		if(this == nullptr|| thisPtr == nullptr ) \
			return ;\
		auto dataTypeObject = qobject_cast< const type_ * >( &other );\
		if( dataTypeObject )\
			type_::operator=( *dataTypeObject );\
		else\
			thisPtr = nullptr;\
	}\
	type_ & operator=( const ITypeObject &other ) override {\
		if(this == nullptr|| thisPtr == nullptr ) \
			return *this;\
		auto dataTypeObject = qobject_cast< const type_ * >( &other );\
		if( dataTypeObject )\
			type_::operator=( *dataTypeObject );\
		else\
			thisPtr = nullptr;\
		return *this;\
	}\
	type_( const type_ &other ) {\
		type_::operator=( other );\
	}

#define Def_Base_Clone_Move_override_function(type_, base_)\
	type_( const ITypeObject &other ) : base_(other) {\
		if(this == nullptr|| thisPtr == nullptr ) \
			return ;\
		auto dataTypeObject = qobject_cast< const type_ * >( &other );\
		if( dataTypeObject )\
			type_::operator=( *dataTypeObject );\
		else\
			thisPtr = nullptr;\
	}\
	type_ & operator=( const ITypeObject &other ) override {\
		if(this == nullptr|| thisPtr == nullptr ) \
			return *this;\
		auto dataTypeObject = qobject_cast< const type_ * >( &other );\
		if( dataTypeObject )\
			type_::operator=( *dataTypeObject );\
		else\
			thisPtr = nullptr;\
		return *this;\
	}\
	type_( const type_ &other ) : base_(other){\
		type_::operator=( other );\
	}

class IVarStack;
class ITypeObject : public QObject, public ISerialize {
	Q_OBJECT;
protected:
	std_vector< QString > uiTypeName;
	std_vector< QString > currentTypeName;
	/// @brief 本身的对象指针
	const ITypeObject *thisPtr;
	std_shared_ptr< IVarStack > varStackSharedPtr;
	std_function< std_shared_ptr< IVarStack > ( ) > getStackFunction;
public:
	ITypeObject( const std_function< std_shared_ptr< IVarStack > ( ) > &get_stack_function_get_function = nullptr, const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr );
	virtual const std_function< std_shared_ptr< IVarStack >( ) > & getGetStackFunction( ) const { return getStackFunction; }
	virtual void setGetStackFunction( const std_function< std_shared_ptr< IVarStack >( ) > &get_stack_function ) { getStackFunction = get_stack_function; }
	ITypeObject( const ITypeObject &other );
	virtual ITypeObject & operator=( const ITypeObject &other );
	/// @brief 比较两个对象。并且返回
	/// @param rhs 右比较对象
	/// @return 返回 0 表示相等，1 表示大于参数，-1 表示小于参数，其他为未知
	virtual int compare( const ITypeObject &rhs ) const {
		if( this == &rhs )
			return 0;
		return 2;
	}

	/// @brief 类型占据大小
	/// @return 大小
	virtual size_t typeMemorySize( ) const =0;
	/// @brief 转换到字符串
	/// @return 字符串
	virtual QString toString( ) const = 0;
	/// @brief 是否是空指针
	/// @return 返回 true 表示空对象
	virtual bool isNullptr( ) const {
		return this == nullptr || thisPtr == nullptr;
	}
	/// @brief 获取类型名称
	/// @return 名称列表
	virtual std_vector< QString > typeNames( ) const {
		return currentTypeName;
	}

	/// @brief 比较 le 与 ri 变量类型，相等返回 0
	/// @tparam TLeft 左侧配置类型
	/// @tparam TRight 右侧配置类型
	/// @param le_ptr 左比较数
	/// @param ri_ptr 右比较数
	/// @param result_ptr 返回比较数
	/// @return 0 表示类型相等
	template< typename TLeft, typename TRight >
		requires requires ( const TLeft *le, const TRight *ri, const TLeft *ta, const ITypeObject *dptr ) {
			le->currentTypeName.size( );
			ta = qobject_cast< const TLeft * >( ri );
			ta->currentTypeName.size( );
			le->currentTypeName.data( )[ 0 ].compare( ta->currentTypeName[ 0 ] );
			dptr = le;
			dptr = ri;
			dptr = ta;
		}
	int comp( const TLeft *le_ptr, const TRight *ri_ptr, const TLeft * &result_ptr ) const {
		if( ri_ptr == le_ptr )
			return 0;
		if( le_ptr->getStack( ) != ri_ptr->getStack( ) )
			return -1;
		result_ptr = qobject_cast< const TLeft * >( ri_ptr );
		if( result_ptr == nullptr )
			return 1;
		size_t typeNameCount = le_ptr->currentTypeName.size( );
		size_t count = result_ptr->currentTypeName.size( );
		if( typeNameCount != count )
			return typeNameCount - count;
		auto leftData = le_ptr->currentTypeName.data( );
		auto rightData = result_ptr->currentTypeName.data( );
		for( count = 0; count < typeNameCount; ++count )
			if( leftData[ count ] != rightData[ count ] )
				return leftData[ count ].compare( rightData[ count ] );
		return 0;
	}

	/// @brief 获取创建该变量的堆栈对象指针
	/// @return 创建该变量的堆栈对象指针
	virtual std_shared_ptr< IVarStack > getStack( ) const {
		if( getStackFunction )
			return getStackFunction( );
		return nullptr;
	}
	/// @brief 创建该变量的堆栈名称列表
	/// @return 创建该变量的堆栈名称列表
	virtual std_vector< QString > getStackTypeNames( ) const;
	/// @brief ui 类型名称
	/// @return ui 类型名称列表
	virtual const std_vector< QString > & getUiTypeNames( ) const { return uiTypeName; }
	/// @brief 配置ui类型名称
	/// @param ui_type_name ui 列表
	virtual void setUiTypeNames( const std_vector< QString > &ui_type_name ) { uiTypeName = ui_type_name; }
	/// @brief 配置ui类型名称
	/// @param ui_type_name ui 列表
	virtual void setUiTypeName( const QString &ui_type_name ) { uiTypeName.emplace_back( ui_type_name ); }
	/// @brief 追加多个ui名称
	/// @param ui_type_name ui 列表 
	virtual void appendUiTypeName( const std_vector< QString > &ui_type_name ) { uiTypeName.append_range( ui_type_name ); }
	/// @brief 追加当个ui名称
	/// @param ui_type_name 追加的 ui 列表
	virtual void appendUiTypeName( const QString &ui_type_name ) { uiTypeName.emplace_back( ui_type_name ); }
};

bool equ( const ITypeObject &left, const void *right );
inline bool operator!=( const ITypeObject &left, std::nullptr_t right ) {
	return !equ( left, ( const void * ) right );
}
inline bool operator==( const ITypeObject &left, std::nullptr_t right ) {
	return equ( left, ( const void * ) right );
}

inline bool operator==( const ITypeObject &left, const void *right ) {
	return equ( left, right );
}

inline bool operator!=( const ITypeObject &left, const void *right ) {
	return !equ( left, right );
}
#endif // ITYPEOBJECT_H_H_HEAD__FILE__
