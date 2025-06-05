#ifndef INTTYPEOBJECT_H_H_HEAD__FILE__
#define INTTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "qt/type/ITypeObject.h"

class IntTypeObject : public ITypeObject {
	Q_OBJECT;
protected:
	int64_t val;
public:
	IntTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ) { }
	IntTypeObject( const int64_t val, QObject *parent = nullptr )
		: ITypeObject( parent ), val( val ) { }
	IntTypeObject( const IntTypeObject &other )
		: ITypeObject( other ),
		val( other.val ) { }
	IntTypeObject & operator=( const IntTypeObject &other ) {
		if( this == &other )
			return *this;
		ITypeObject::operator =( other );
		val = other.val;
		return *this;
	}
	IntTypeObject & operator=( const int64_t &right ) {
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
		return "IntTypeObject";
	}
	bool isNullptr( ) const override {
		return false;
	}
};

#endif // INTTYPEOBJECT_H_H_HEAD__FILE__
