#ifndef STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#define STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class QLabel;
class NodeItemInfoItemWidget;
class QVBoxLayout;
class QScrollArea;
class NodeItemInfoListWidget;
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
	NodeItemInfo *currentNodeItemInfo;
protected:
	const NodeItemInfo *errorNodeItemInfo;
protected:
	Application *application;
	NodeDirector *nodeDirector;
	VarGenerate *varGenerate;
	QPushButton *updateBtn;
	std_vector_pairt< NodeItemInfo *, QLabel * > allRenderNodeInfo;
protected:
	virtual void updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info );
	virtual void fillLinkNodeInfoListWidget( );
	virtual void clearRenderNodeInfo();
	virtual void updateLayout();
public:
	StartNodeInfoWidget( NodeItem *node_item );
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // STARTNODEINFOWIDGET_H_H_HEAD__FILE__
