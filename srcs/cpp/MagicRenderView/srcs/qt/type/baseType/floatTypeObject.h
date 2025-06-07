#ifndef FLOATTYPEOBJECT_H_H_HEAD__FILE__
#define FLOATTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "qt/type/ITypeObject.h"

class FloatTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	double_t val;
public:
	operator_equ( FloatTypeObject, val );
public:
	FloatTypeObject( const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr ) : ITypeObject( alias_type_name, parent ), val( 0 ) { }
	FloatTypeObject( const FloatTypeObject &other )
		: ITypeObject( other.currentTypeName, other.parent( ) ), val( other.val ) {
	}
	FloatTypeObject( const double_t val, const std_vector< QString > &alias_type_name = { }, QObject *parent = nullptr )
		: ITypeObject( alias_type_name, parent ), val( val ) {
		currentTypeName.emplace_back( FloatTypeObject::staticMetaObject.className( ) );
	}
	FloatTypeObject & operator=( const FloatTypeObject &other ) {
		if( this == &other )
			return *this;
		ITypeObject::operator=( other );
		val = other.val;
		return *this;
	}

	int compare( const ITypeObject &rhs ) const override {
		decltype(this) result_ptr;
		int result = comp( this, &rhs, result_ptr );
		if( result == 0 && result_ptr != this )
			return this->val - result_ptr->val;
		return result;
	}
	size_t typeMemorySize( ) const override {
		return sizeof val;
	}
	QString toString( ) const override {
		return QString::number( val );
	}
	bool isNullptr( ) const override {
		return false;
	}
	~FloatTypeObject( ) override {
	}
};

#endif // FLOATTYPEOBJECT_H_H_HEAD__FILE__
