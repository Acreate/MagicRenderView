#ifndef NODEITEMINFOITEMWIDGET_H_H_HEAD__FILE__
#define NODEITEMINFOITEMWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QLabel>
#include <qwidget.h>

class NodeItemInfo;
class NodeItemInfoItemWidget : public QLabel {
	Q_OBJECT;
public:
	NodeItemInfo *nodeItemInfo;
public:
	NodeItemInfoItemWidget( NodeItemInfo *node_item_item_info, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	~NodeItemInfoItemWidget( ) override {
		emit releaseThisPtr( this );
	}
	virtual NodeItemInfo * getNodeItemInfo( ) const { return nodeItemInfo; }
protected:
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
Q_SIGNALS:
	void clickNodeItemWidget( NodeItemInfoItemWidget *send_obj_ptr, NodeItemInfo *click_node_item_ptr );
	void releaseThisPtr( NodeItemInfoItemWidget *release_node_item );
};

#endif // NODEITEMINFOITEMWIDGET_H_H_HEAD__FILE__
