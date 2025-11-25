#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__
#pragma once
#include <QApplication>

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
protected:
	MainWindow *mainWindow;
protected:
	QSize mainWindowBuffSize;
	QSize mainWindowSize;
	QPoint mainWindowBuffPoint;
	QPoint mainWindowPoint;
	Qt::WindowStates mainWindowState;
protected:
	QString iniSaveFilePathName;
public:
	Application( int &argc, char **argv, int i = ApplicationFlags );
	~Application( ) override;

	bool notify( QObject *, QEvent * ) override;
protected:
	bool event( QEvent * ) override;
public:
	virtual bool init( );
	virtual NodeDirector * getNodeDirector( ) const { return nodeDirector; }
	virtual PrinterDirector * getPrinterDirector( ) const { return printerDirector; }
	virtual VarDirector * getVarDirector( ) const { return varDirector; }
	virtual MainWindow * getMainWindow( ) const { return mainWindow; }
	virtual bool setVar( const QString &var_key, const std::vector< uint8_t > &var_value ) const;
	virtual bool getVar( const QString &result_var_key, std::vector< uint8_t > &result_var_value ) const;
	virtual bool removeVar( const QString &result_var_key ) const;
	virtual bool synchronousFileToVar( ) const;
	virtual bool synchronousVarToFile( ) const;
	virtual bool synchronousWindowInfoToVar( ) const;
	virtual bool synchronousVarToWindowInfo( );
	virtual void clearVar( );
	virtual bool createFile( const QString &create_file_path_name ) const;
	virtual bool removeFile( const QString &remove_file_path_name ) const;
	virtual bool createDir( const QString &create_file_path_name ) const;
	virtual bool removeDir( const QString &remove_file_path_name ) const;
	virtual bool hasFile( const QString &check_file_path_name ) const;
	virtual bool hasDir( const QString &check_dir_path_name ) const;
	virtual bool getPathHasFileInfo( const QString &check_dir_path_name, QFileInfo &result_file_info ) const;
	virtual bool widgetMoveTargetDispyer( QWidget *move_widget, const size_t &displyer_index ) const;
	virtual bool widgetMoveTargetDispyer( const size_t &displyer_index ) const;
	virtual bool widgetAllMoveTargetDispyer( const size_t &displyer_index ) const;
};

#endif // APPLICATION_H_H_HEAD__FILE__
