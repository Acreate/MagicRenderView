#ifndef NULLTYPEOBJECT_H_H_HEAD__FILE__
#define NULLTYPEOBJECT_H_H_HEAD__FILE__
#pragma once
#include "qt/type/ITypeObject.h"

class NullTypeObject : public ITypeObject {
	Q_OBJECT;
public:
	NullTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ) { }
	size_t typeMemorySize( ) const override {
		return 0;
	}
	QString toString( ) const override {
		return "nullptr";
	}
	QString typeName( ) const override {
		return "NullTypeObject";
	}
	bool isNullptr( ) const override {
		return true;
	}
};

#endif // NULLTYPEOBJECT_H_H_HEAD__FILE__
