#ifndef ITYPEOBJECT_H_H_HEAD__FILE__
#define ITYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include <QObject>

#include "alias/type_alias.h"

#define operator_equ( Type, Return_var )\
	operator uint8_t( ) const {\
		return Return_var;\
	}\
	operator uint16_t( ) const {\
		return Return_var;\
	}\
	operator uint32_t( ) const {\
		return Return_var;\
	}\
	operator uint64_t( ) const {\
		return Return_var;\
	}\
	operator int8_t( ) const {\
		return Return_var;\
	}\
	operator int16_t( ) const {\
		return Return_var;\
	}\
	operator int32_t( ) const {\
		return Return_var;\
	}\
	operator int64_t( ) const {\
		return Return_var;\
	}\
	operator float( ) const {\
		return Return_var;\
	}\
	operator double( ) const {\
		return Return_var;\
	}\
	Type & operator=( const int8_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const int16_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const int32_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const int64_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const uint8_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const uint16_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const uint32_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const uint64_t &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const float &right ) {\
		Return_var = right;\
		return *this;\
	}\
	Type & operator=( const double &right ) {\
		Return_var = right;\
		return *this;\
	}

class ITypeObject : public QObject {
	Q_OBJECT;
protected:
	std_vector< QString > currentTypeName;
public:
	ITypeObject( const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr ) : QObject( parent ) {
		currentTypeName.emplace_back( ITypeObject::staticMetaObject.className( ) );

		size_t count = alias_type_name.size( );
		if( count == 0 )
			return;
		auto datas = alias_type_name.data( );
		size_t newsize = 1 + count;
		// 扩张
		currentTypeName.resize( newsize );
		auto targetPtr = currentTypeName.data( );
		for( size_t index = 1; index < newsize; ++index )
			targetPtr[ index ] = datas[ index - 1 ];
	}
	ITypeObject( const ITypeObject &other )
		: QObject( other.parent( ) ) {
		currentTypeName = other.currentTypeName;
	}
	ITypeObject & operator=( const ITypeObject &other ) {
		if( this == &other )
			return *this;
		setParent( other.parent( ) );
		currentTypeName = other.currentTypeName;
		return *this;
	}
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
	virtual bool isNullptr( ) const = 0;
	/// @brief 获取类型名称
	/// @return 名称列表
	virtual std_vector< QString > typeNames( ) const {
		return currentTypeName;
	}

	
	template< typename TLeft, typename TRight >
		requires requires ( const TLeft *le, const TRight *ri, const TLeft *ta ) {
			le->currentTypeName.size( );
			ta = qobject_cast< const TLeft * >( ri );
			ta->currentTypeName.size( );
			le->currentTypeName.data( )[ 0 ].compare( ta->currentTypeName[ 0 ] );
		}
	int comp( const TLeft *le_ptr, const TRight *ri_ptr , const TLeft* &result_ptr ) const {
		if( ri_ptr == le_ptr )
			return 0;
		result_ptr = qobject_cast< const TLeft * >( ri_ptr );
		if( result_ptr == nullptr  )
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
	
};

#endif // ITYPEOBJECT_H_H_HEAD__FILE__
