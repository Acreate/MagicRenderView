#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once
#include <QMainWindow>
class DrawNodeWidget;
class DrawLinkWidget;
class NodeDirector;
class MainWidgetScrollArea;
class MainWidget;
class Application;
class MainWindow : public QMainWindow {
	Q_OBJECT;
	friend class Application;
protected:
	MainWidgetScrollArea *mainWidgetScrollArea;
	MainWidget *mainWidget;
	DrawNodeWidget *drawNodeWidget;
	DrawLinkWidget *drawLinkWidget;
	Application *instancePtr;
	NodeDirector *nodeDirector;
protected:
	MainWindow( );
	virtual bool init( );
public:
	~MainWindow( ) override;
	virtual MainWidgetScrollArea * getMainWidgetScrollArea( ) const { return mainWidgetScrollArea; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	bool event( QEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
