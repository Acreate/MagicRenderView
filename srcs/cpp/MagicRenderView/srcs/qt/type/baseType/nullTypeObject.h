#ifndef NULLTYPEOBJECT_H_H_HEAD__FILE__
#define NULLTYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "qt/type/ITypeObject.h"

class NullTypeObject : public ITypeObject {
	Q_OBJECT;
public:
	static bool isNullptr( const ITypeObject *object ) {
		if( object == nullptr || qobject_cast< const NullTypeObject * >( object ) )
			return true;
		return object->isNullptr( );
	}
public:
	NullTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ) { }
	size_t typeMemorySize( ) const override {
		return 0;
	}

	int compare( const ITypeObject &rhs ) const override {
		auto typeObject = &rhs;
		if( this == typeObject )
			return true;
		if( typeObject == nullptr || qobject_cast< const NullTypeObject * >( typeObject ) )
			return true;
		return typeObject->isNullptr( );
	}

	QString toString( ) const override {
		return "nullptr";
	}
	bool isNullptr( ) const override {
		return true;
	}
};

#endif // NULLTYPEOBJECT_H_H_HEAD__FILE__
