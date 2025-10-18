#ifndef NODEITEMINFOWIDGET_H_H_HEAD__FILE__
#define NODEITEMINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include "nodeItemInfoScrollAreaWidget.h"

#include <alias/type_alias.h>

class Application;
class NodeDirector;
class NodeItemInfo;
class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class NodeItem;
class NodeItemInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
	NodeDirector *nodeDirector;
	NodeItemInfo *nodeItemInfoTarget;
	Application *applicationInstancePtr;
public:
	NodeItemInfoWidget( NodeItem *node_item, QWidget *parent = nullptr );
	virtual NodeItem * getNodeItem( ) const { return nodeItem; }
	virtual NodeItemInfo * getNodeItemInfoTarget( ) const { return nodeItemInfoTarget; }
};

#endif // NODEITEMINFOWIDGET_H_H_HEAD__FILE__
