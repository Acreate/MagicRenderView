#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once
#include <QApplication>

class AppDirector;
class ApplicationMenuStack;
class NormalApplicationMenu;
class MenuDirector;
class QFileInfo;
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
	MenuDirector *menuDirector;
	AppDirector *appDirector;
protected:
	MainWindow *mainWindow;
	ApplicationMenuStack *applicationMenuStack;
protected:
	QSize mainWindowBuffSize;
	QSize mainWindowSize;
	QPoint mainWindowBuffPoint;
	QPoint mainWindowPoint;
	Qt::WindowStates mainWindowState;
protected:
	QDateTime *appInitRunDataTime;
protected:
	QString iniSaveFilePathName;
	QString logSaveFilePathName;
protected:
	
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	~Application( ) override;
	bool notify( QObject *, QEvent * ) override;
protected:
	bool event( QEvent * ) override;
protected:
	virtual bool synchronousWindowInfoToVar( ) const;
	virtual bool synchronousVarToWindowInfo( );
public:
	virtual bool init( );
	virtual ApplicationMenuStack * getApplicationMenuStack( ) const { return applicationMenuStack; }
	virtual const QDateTime * getAppInitRunDataTime( ) const { return appInitRunDataTime; }
	virtual const QString & getIniSaveFilePathName( ) const { return iniSaveFilePathName; }
	virtual const QString & getLogSaveFilePathName( ) const { return logSaveFilePathName; }
	virtual AppDirector * getAppDirector( ) const { return appDirector; }
	virtual NodeDirector * getNodeDirector( ) const { return nodeDirector; }
	virtual PrinterDirector * getPrinterDirector( ) const { return printerDirector; }
	virtual VarDirector * getVarDirector( ) const { return varDirector; }
	virtual MenuDirector * getMenuDirector( ) const { return menuDirector; }
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	virtual bool setVar( const QString &var_key, const std::vector< uint8_t > &var_value ) const;
	virtual bool getVar( const QString &result_var_key, std::vector< uint8_t > &result_var_value ) const;
	virtual bool removeVar( const QString &result_var_key ) const;
	virtual bool synchronousFileToVar( ) const;
	virtual bool synchronousVarToFile( ) const;
	virtual void clearVar( );
	virtual bool widgetMoveTargetDispyer( QWidget *move_widget, const size_t &displyer_index ) const;
	virtual bool widgetMoveTargetDispyer( const size_t &displyer_index ) const;
	virtual bool widgetAllMoveTargetDispyer( const size_t &displyer_index ) const;
};

#endif // APPLICATION_H_H_HEAD__FILE__
