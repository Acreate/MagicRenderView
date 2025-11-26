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
public:
	DrawLinkWidget( QWidget *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
};

#endif // DRAWLINKWIDGET_H_H_HEAD__FILE__
