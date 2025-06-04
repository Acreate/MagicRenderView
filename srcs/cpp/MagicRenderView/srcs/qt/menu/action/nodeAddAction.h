#ifndef NODEADDACTION_H_H_HEAD__FILE__
#define NODEADDACTION_H_H_HEAD__FILE__
#pragma once

#include <QAction>

#include "alias/type_alias.h"
class IFunctionDeclaration;
class NodeAddAction : public QAction {
	Q_OBJECT;
protected:
	std_shared_ptr< IFunctionDeclaration > functionDeclaration;
public:
	NodeAddAction( QObject *parent, const std_shared_ptr< IFunctionDeclaration > &function_declaration );
	~NodeAddAction( ) override;
};

#endif // NODEADDACTION_H_H_HEAD__FILE__
