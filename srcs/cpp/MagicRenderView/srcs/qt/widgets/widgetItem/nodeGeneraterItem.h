#ifndef NODEGENERATERITEM_H_H_HEAD__FILE__
#define NODEGENERATERITEM_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include "../../../alias/type_alias.h"

class IFunStack;
class NodeGeneraterItem : public QObject {
	Q_OBJECT;
protected:
	std_shared_ptr< IFunStack > funStack;
public:
	NodeGeneraterItem(const std_shared_ptr< IFunStack > &fun_stack, QObject *parent = nullptr );
	virtual const std_shared_ptr< IFunStack > & getFunStack( ) const { return funStack; }
};

#endif // NODEGENERATERITEM_H_H_HEAD__FILE__
