#ifndef NODEADDACTION_H_H_HEAD__FILE__
#define NODEADDACTION_H_H_HEAD__FILE__
#pragma once

#include <QAction>

#include "alias/type_alias.h"
class IFunctionDeclaration;
class NodeAddAction : public QAction {
	Q_OBJECT;
protected:
	QString functionName;
public:
	NodeAddAction( QObject *parent, const QString &function_name );
	~NodeAddAction( ) override;
	const QString & getFunctionName( ) const { return functionName; }
};

#endif // NODEADDACTION_H_H_HEAD__FILE__
