#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once
#include <QMainWindow>

class NodeRunInfo;
namespace NodeEnum {
	enum class CreateType;
	enum class AdviseType;
	enum class ErrorType;
}
class OutputPort;
class InputPort;
class SrackInfo;
class Node;
class PrinterDirector;
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
	Application *instancePtr;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	QString saveFileDirPath;
	QMenuBar *appMenuBar;
	QMenu *fileMenu;
	QMenu *projectMenu;
	QToolBar *fileToolBar;
	QToolBar *projectToolBar;
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
Q_SIGNALS:
	void release_signal( MainWindow *release_ptr );
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
