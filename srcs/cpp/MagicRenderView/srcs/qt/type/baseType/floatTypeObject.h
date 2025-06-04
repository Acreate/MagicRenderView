#ifndef FLOATTYPEOBJECT_H_H_HEAD__FILE__
#define FLOATTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "qt/type/ITypeObject.h"

class FloatTypeObject : public ITypeObject {
	Q_OBJECT;
public:
	FloatTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ) { }
};

#endif // FLOATTYPEOBJECT_H_H_HEAD__FILE__
