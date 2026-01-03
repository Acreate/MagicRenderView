#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once
#include <QMainWindow>

class NormalApplicationToolBar;
class NormalApplicationAction;
class NormalApplicationMenu;
class BuilderApplicationMenu;
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
	NormalApplicationMenu *projectMenu;
	NormalApplicationMenu *builderMenu;
	NormalApplicationMenu *appMenu;
	NormalApplicationMenu *editorMenu;
	NormalApplicationToolBar *projectToolBar;
	NormalApplicationToolBar *builderToolBar;
protected:
	MainWindow( );
	virtual bool init( );
protected Q_SLOTS:
	virtual void triggActionSignal( NormalApplicationAction *action );
	virtual void triggMenuActionSignal( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action );
	virtual void triggToolbarActionSignal( NormalApplicationToolBar *normal_application_tool_bar, NormalApplicationAction *action );
public:
	~MainWindow( ) override;
	virtual MainWidgetScrollArea * getMainWidgetScrollArea( ) const { return mainWidgetScrollArea; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual bool builderNodeProject( );
	virtual bool nextStepBuilderNode( );
	virtual bool runBuilderBuilderNode( );
	virtual bool stopBuilderBuilderNode( );
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	bool event( QEvent *event ) override;
protected:
Q_SIGNALS:
	void release_signal( MainWindow *release_ptr );
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
