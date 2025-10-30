#ifndef STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#define STARTNODEINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include <alias/type_alias.h>

class QVBoxLayout;
class QScrollArea;
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
	std_vector_pairt< NodeItemInfo *, std_pairt< QImage *, QPoint > > allRenderNodeInfo;
protected:
	virtual void updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info );
	virtual void fillLinkNodeInfoListWidget( );
	virtual void clearRenderNodeInfo( );
	virtual void updateLayout( );
public:
	StartNodeInfoWidget( NodeItem *node_item );
protected:
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
Q_SIGNALS:
	void clickNodeItemSig( StartNodeInfoWidget *sender_sig_ptr, NodeItemInfo *clickNodeInfo );
};

#endif // STARTNODEINFOWIDGET_H_H_HEAD__FILE__
