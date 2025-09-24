#ifndef I_TYPE_H_H_HEAD__FILE__
#define I_TYPE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../alias/type_alias.h"

/// @brief 类型接口
class I_Type : public QObject {
	Q_OBJECT;
protected:
	const type_info &typeInfo;
protected:
public:
	I_Type( type_info &type_info );
	I_Type( const type_info &type_info );
	~I_Type( ) override;
	I_Type( const I_Type &other );
	friend bool operator==( const I_Type &lhs, const I_Type &rhs );
	friend bool operator!=( const I_Type &lhs, const I_Type &rhs ) { return !( lhs == rhs ); }
	virtual const type_info & getTypeInfo( ) const { return typeInfo; }
};

#endif // I_TYPE_H_H_HEAD__FILE__
