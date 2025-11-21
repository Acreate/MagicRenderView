#ifndef DRAWNODEWIDGET_H_H_HEAD__FILE__
#define DRAWNODEWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class Application;
class NodeDirector;
class DrawNodeWidget : public QWidget {
	Q_OBJECT;
protected:
	Application *appInstancePtr;
	NodeDirector *nodeDirector;
public:
	DrawNodeWidget( QWidget *parent, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
};

#endif // DRAWNODEWIDGET_H_H_HEAD__FILE__
