#ifndef APPLICATIONMENUSTACK_H_H_HEAD__FILE__
#define APPLICATIONMENUSTACK_H_H_HEAD__FILE__
#pragma once

#include <QObject>

class NormalApplicationAction;
class NormalApplicationMenu;
class NormalApplicationToolBar;
class Application;
class MainWindow;
class QAction;
class QMenu;
class QToolBar;
class ApplicationMenuStack : public QObject {
	Q_OBJECT;
protected:
	Application *application;
public:
	ApplicationMenuStack( QObject *parent = nullptr );
	virtual bool initStack( );
	virtual NormalApplicationToolBar * getToolBar( const QString &tool_menu_name );
	virtual NormalApplicationMenu * getMenu( const QString &tool_menu_name );
	virtual NormalApplicationAction * getAction( const QString &acton_name );
};
#endif // APPLICATIONMENUSTACK_H_H_HEAD__FILE__
