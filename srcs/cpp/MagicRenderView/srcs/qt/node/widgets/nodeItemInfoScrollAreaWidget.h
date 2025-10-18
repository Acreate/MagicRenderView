#ifndef NODEITEMINFOSCROLLAREAWIDGET_H_H_HEAD__FILE__
#define NODEITEMINFOSCROLLAREAWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class NodeItem;
class NodeItemInfoWidget;
class NodeItemInfoScrollAreaWidget : public QScrollArea {
	Q_OBJECT;
protected:
	NodeItemInfoWidget *contentWdiget;
	NodeItem *nodeItem;
public:
	NodeItemInfoScrollAreaWidget( NodeItem *node_item, QWidget *parent = nullptr );
	NodeItemInfoScrollAreaWidget( NodeItemInfoWidget *content_wdiget, NodeItem *node_item, QWidget *parent = nullptr );
	virtual NodeItemInfoWidget * getContentWdiget( ) const { return contentWdiget; }
};

#endif // NODEITEMINFOSCROLLAREAWIDGET_H_H_HEAD__FILE__
