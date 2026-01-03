#ifndef NORMALAPPLICATIONACTION_H_H_HEAD__FILE__
#define NORMALAPPLICATIONACTION_H_H_HEAD__FILE__
#pragma once
#include <QAction>
#include <QWidget>

class MainWindow;
class AppDirector;
class VarDirector;
class PrinterDirector;
class NodeDirector;
class Application;
class ApplicationMenuStack;
class NormalApplicationAction : public QAction {
	Q_OBJECT;
protected:
	Application *application;
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	VarDirector *varDirector;
	AppDirector *appDirector;
private:
	void triggered( );
protected:
	virtual void setInitVarNumber( const QString &name ) {
		setText( name );
		setObjectName( name );
	}
public:
	~NormalApplicationAction( ) override;
	virtual bool init( ApplicationMenuStack *application_menu_stack_ptr );
	virtual bool run( MainWindow* parent ) = 0;
Q_SIGNALS:
	void release_signal( NormalApplicationAction *action );
	void trigg_signal( NormalApplicationAction *action );
};

#endif // NORMALAPPLICATIONACTION_H_H_HEAD__FILE__
