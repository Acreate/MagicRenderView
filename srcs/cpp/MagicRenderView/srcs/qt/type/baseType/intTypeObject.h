#ifndef INTTYPEOBJECT_H_H_HEAD__FILE__
#define INTTYPEOBJECT_H_H_HEAD__FILE__
#pragma once


#include "qt/type/ITypeObject.h"

class IntTypeObject : public ITypeObject {
	Q_OBJECT;
public:
	IntTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ) { }
};



#endif // INTTYPEOBJECT_H_H_HEAD__FILE__
