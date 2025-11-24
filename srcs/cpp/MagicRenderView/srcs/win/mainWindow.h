#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once
#include <QMainWindow>
class NodeDirector;
class MainWidgetScrollArea;
class MainWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
	friend class Application;
protected:
	MainWidgetScrollArea *mainWidgetScrollArea;
	MainWidget *mainWidget;
	Application *instancePtr;
	NodeDirector *nodeDirector;
	QMenu *nodeCreateMenu;
protected:
	MainWindow( );
	virtual bool init( );
public:
	virtual MainWidgetScrollArea * getMainWidgetScrollArea( ) const { return mainWidgetScrollArea; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
