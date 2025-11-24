#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once
#include <QApplication>

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
protected:
	MainWindow *mainWindow;
protected:
	std::vector< std::pair< QString, std::vector< uint8_t > > > iniData;
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	~Application( ) override;
	virtual bool init( );
	virtual NodeDirector * getNodeDirector( ) const { return nodeDirector; }
	virtual PrinterDirector * getPrinterDirector( ) const { return printerDirector; }
	virtual VarDirector * getVarDirector( ) const { return varDirector; }
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	virtual bool setVar( const QString &var_key, const std::vector< uint8_t > &var_value );
	virtual bool getVar( const QString &result_var_key, std::vector< uint8_t > &result_var_value );
	virtual bool removeVar( const QString &result_var_key );

};

#endif // APPLICATION_H_H_HEAD__FILE__
