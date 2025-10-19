#ifndef STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#define STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class QPushButton;
class NodeItemInfo;
class VarGenerate;
class NodeDirector;
class Application;
class NodeItem;
class StartNodeInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
	NodeItemInfo *nodeItemInfo;
	std_vector<NodeItemInfo *> builderVector;
	Application *application;
	NodeDirector *nodeDirector;
	VarGenerate *varGenerate;
	QWidget *toolBtnVector;
	QPushButton *runBtn;
	QPushButton *builderBtn;
protected:
	virtual void run( );
	virtual void builder( );
	virtual void updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info );
	virtual void toolWidgetMoveToMid( );
public:
	StartNodeInfoWidget( NodeItem *node_item );
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // STARTNODEINFOWIDGET_H_H_HEAD__FILE__
