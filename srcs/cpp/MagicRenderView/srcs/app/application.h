#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once
#include <QApplication>

class IniDirector;
class MainWindow;
class VarDirector;
class PrinterDirector;
class NodeDirector;
class Application : public QApplication {
	Q_OBJECT;
protected:
	static Application *instance;
public:
	static Application * getInstancePtr( );
protected:
	NodeDirector *nodeDirector;
	PrinterDirector *printerDirector;
	VarDirector *varDirector;
	IniDirector *iniDirector;
protected:
	MainWindow *mainWindow;
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	~Application( ) override;
	virtual bool init( );
	virtual NodeDirector * getNodeDirector( ) const { return nodeDirector; }
	virtual PrinterDirector * getPrinterDirector( ) const { return printerDirector; }
	virtual VarDirector * getVarDirector( ) const { return varDirector; }
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	virtual IniDirector * getIniDirector( ) const { return iniDirector; }
};

#endif // APPLICATION_H_H_HEAD__FILE__
