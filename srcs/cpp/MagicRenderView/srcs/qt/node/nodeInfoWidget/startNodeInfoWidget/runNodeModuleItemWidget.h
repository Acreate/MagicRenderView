#ifndef RUNNODEMODULEITEMWIDGET_H_H_HEAD__FILE__
#define RUNNODEMODULEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QLabel>

class NodeItem;
class RunNodeModuleItemWidget : public QLabel {
	Q_OBJECT;
protected:
	NodeItem *nodeItemPtr;
	QString titile;
	QImage titleBuff;
	int penWidth;
	int doublePenWidth;
public:
	RunNodeModuleItemWidget( NodeItem *node_item_ptr, QWidget *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual NodeItem * getNodeItemPtr( ) const { return nodeItemPtr; }
	virtual const QString & getTitile( ) const { return titile; }
	virtual void setTitile( const QString &titile );
protected:
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent * ) override;
};

#endif // RUNNODEMODULEITEMWIDGET_H_H_HEAD__FILE__
