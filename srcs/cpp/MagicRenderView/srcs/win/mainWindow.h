#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#pragma once
#include <QMainWindow>

class PrinterDirector;
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
	PrinterDirector *printerDirector;
	QToolBar *fileToolBar;
	QToolBar *projectToolBar;
	QString saveFileDirPath;
	std::vector< QShortcut * > shortcutVector;
	std::vector< QAction * > actionVector;
	QMenuBar *appMenuBar;
	QMenu *fileMenu;
	QMenu *projectMenu;
protected:
	MainWindow( );
	virtual bool init( );
public:
	~MainWindow( ) override;
	virtual MainWidgetScrollArea * getMainWidgetScrollArea( ) const { return mainWidgetScrollArea; }
	virtual DrawNodeWidget * getDrawNodeWidget( ) const { return drawNodeWidget; }
	virtual DrawLinkWidget * getDrawLinkWidget( ) const { return drawLinkWidget; }
	virtual MainWidget * getMainWidget( ) const { return mainWidget; }
	virtual void savePorjectToFile( );
	virtual void loadPorjectAtFile( );
	virtual void unDownloadPorjectAtFile( );
	virtual void copyNodeInfo( );
	virtual void pasteNodeInfo( );
	virtual void cutNodeInfo( );
	virtual void cancelNodeInfo( );
	virtual void deleteNodeInfo( );
	virtual void builderProject( );
	virtual void runAllProject( );
	virtual void runNextProject( );
	virtual void stopProject( );
	virtual void clearProject( );
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
	bool event( QEvent *event ) override;
Q_SIGNALS:
	void release_signal( MainWindow *release_ptr );
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
