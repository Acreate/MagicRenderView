#ifndef NODEADDACTION_H_H_HEAD__FILE__
#define NODEADDACTION_H_H_HEAD__FILE__
#pragma once

#include <QAction>
class NodeAddAction : public QAction {
	Q_OBJECT;
public:
	NodeAddAction( QObject * parent );
	~NodeAddAction() override;
};

#endif // NODEADDACTION_H_H_HEAD__FILE__
