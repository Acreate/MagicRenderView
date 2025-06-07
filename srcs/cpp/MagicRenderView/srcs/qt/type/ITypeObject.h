#ifndef ITYPEOBJECT_H_H_HEAD__FILE__
#define ITYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include <QObject>

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
public:
	ITypeObject( QObject *parent ) : QObject( parent ) { }
	ITypeObject( const ITypeObject &other )
		: QObject( other.parent( ) ) {
	}
	ITypeObject & operator=( const ITypeObject &other ) {
		if( this == &other )
			return *this;
		setParent( other.parent( ) );
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
};

#endif // ITYPEOBJECT_H_H_HEAD__FILE__
