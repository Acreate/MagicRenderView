#ifndef INODECOMPONENT_H_H_HEAD__FILE__
#define INODECOMPONENT_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "alias/type_alias.h"

class ITypeObject;
class INodeComponent : public QWidget {
	Q_OBJECT;
protected:
	std_shared_ptr< ITypeObject > varObject;
public:
	virtual const std_shared_ptr< ITypeObject > & getVarObject( ) const { return varObject; }
	virtual const ITypeObject * getVarObjectPtr( ) const { return varObject.get( ); }
};

#endif // INODECOMPONENT_H_H_HEAD__FILE__
