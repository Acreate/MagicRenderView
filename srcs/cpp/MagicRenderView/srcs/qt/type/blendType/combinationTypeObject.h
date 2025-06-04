#ifndef COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
#define COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
#pragma once

#include "qt/type/ITypeObject.h"

class CombinationTypeObject : public ITypeObject {
	Q_OBJECT;
public:
	CombinationTypeObject( QObject *parent = nullptr ) : ITypeObject( parent ) { }
};


#endif // COMBINATIONTYPEOBJECT_H_H_HEAD__FILE__
