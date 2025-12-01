#ifndef DRAWLINKWIDGET_H_H_HEAD__FILE__
#define DRAWLINKWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class Application;
class NodeDirector;
class DrawLinkWidget : public QWidget {
	Q_OBJECT;
	friend class MainWidget;
	friend class MainWindow;
protected:
	Application *appInstancePtr;
	NodeDirector *nodeDirector;
	QPoint startPoint;
	QPoint endPoint;
	bool isDrawLine;
public:
	DrawLinkWidget( QWidget *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void drawBegin( const QPoint &start_point );
	virtual void drawLinePoint( const QPoint &end_point );
	virtual void drawEnd( );
protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
};

#endif // DRAWLINKWIDGET_H_H_HEAD__FILE__
