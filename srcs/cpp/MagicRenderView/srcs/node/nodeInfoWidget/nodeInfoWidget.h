#ifndef NODEINFOWIDGET_H_H_HEAD__FILE__
#define NODEINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QScrollArea>

class Node;
class MainWindow;
class NodeInfoWidget : public QScrollArea {
	Q_OBJECT;
protected:
public:
	NodeInfoWidget( MainWindow *parent );
	virtual bool fitterType( Node *check_node_ptr ) const;
protected:
	void hideEvent( QHideEvent *event ) override;
	void showEvent( QShowEvent *event ) override;
};

#endif // NODEINFOWIDGET_H_H_HEAD__FILE__
