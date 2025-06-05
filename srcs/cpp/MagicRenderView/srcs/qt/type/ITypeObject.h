#ifndef ITYPEOBJECT_H_H_HEAD__FILE__
#define ITYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
class ITypeObject : public QObject {
	Q_OBJECT;
public:
	ITypeObject( QObject *parent = nullptr ) : QObject( parent ) { }
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
	/// @brief 类型名称
	/// @return 类型名称字符串表现
	virtual QString typeName( ) const =0;
	/// @brief 是否是空指针
	/// @return 返回 true 表示空对象
	virtual bool isNullptr( ) const = 0;
};

#endif // ITYPEOBJECT_H_H_HEAD__FILE__
