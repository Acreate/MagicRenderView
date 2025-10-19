#ifndef STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#define STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class VarGenerate;
class NodeDirector;
class Application;
class NodeItem;
class StartNodeInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
	Application *application;
	NodeDirector *nodeDirector;
	VarGenerate *varGenerate;
public:
	StartNodeInfoWidget( NodeItem *node_item )
		: nodeItem( node_item ) { }
	
};

#endif // STARTNODEINFOWIDGET_H_H_HEAD__FILE__
