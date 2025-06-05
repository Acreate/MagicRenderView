#ifndef FLOATTYPEOBJECT_H_H_HEAD__FILE__
#define FLOATTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "qt/type/ITypeObject.h"

class FloatTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	double_t val;
public:
	FloatTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ) { }
	FloatTypeObject( const FloatTypeObject &other )
		: val( other.val ) {
		setParent( other.parent( ) );
	}
	FloatTypeObject & operator=( const FloatTypeObject &other ) {
		if( this == &other )
			return *this;
		setParent( other.parent( ) );
		val = other.val;
		return *this;
	}
	FloatTypeObject( const double_t val, QObject *parent = nullptr )
		: ITypeObject( parent ), val( val ) { }
	FloatTypeObject & operator=( const double_t &right ) {
		val = right;
		return *this;
	}
	size_t typeMemorySize( ) const override {
		return sizeof val;
	}
	QString toString( ) const override {
		return QString::number( val );
	}
	QString typeName( ) const override {
		return "FloatTypeObject";
	}
	bool isNullptr( ) const override {
		return false;
	}
};

#endif // FLOATTYPEOBJECT_H_H_HEAD__FILE__
