#ifndef NODESCRIPTSWIDGET_H_H_HEAD__FILE__
#define NODESCRIPTSWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class Application;
class NodeScriptsWidget : public QWidget {
	Q_OBJECT;
protected:
	Application *applicationInstancePtr;
public:
	NodeScriptsWidget( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~NodeScriptsWidget( ) override;
protected:
	void paintEvent( QPaintEvent *event ) override;
protected Q_SLOTS :
	void dragEventEnd( Application *event_obj, QWidget *draw_widget );
};
#endif // NODESCRIPTSWIDGET_H_H_HEAD__FILE__
