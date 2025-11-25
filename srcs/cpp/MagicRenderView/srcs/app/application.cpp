#include "application.h"

#include <QDir>
#include <QScreen>
#include <qfile.h>
#include <qfileinfo.h>

#include "../director/iniDirector.h"
#include "../director/nodeDirector.h"
#include "../director/printerDirector.h"
#include "../director/varDirector.h"

#include "../win/mainWindow.h"

Application *Application::instance = nullptr;
Application * Application::getInstancePtr( ) {
	return instance;
}

Application::Application( int &argc, char **argv, int i ) : QApplication( argc, argv, i ), mainWindow( nullptr ), iniDirector( nullptr ), varDirector( nullptr ), printerDirector( nullptr ), nodeDirector( nullptr ) {
}
Application::~Application( ) {
	if( mainWindow )
		delete mainWindow;
	if( nodeDirector )
		delete nodeDirector;
	if( iniDirector )
		delete iniDirector;
	if( varDirector )
		delete varDirector;
	if( printerDirector )
		delete printerDirector;
}
bool Application::init( ) {
	Application::instance = this;

	if( mainWindow )
		delete mainWindow;
	if( nodeDirector )
		delete nodeDirector;
	if( iniDirector )
		delete iniDirector;
	if( varDirector )
		delete varDirector;
	if( printerDirector )
		delete printerDirector;

	printerDirector = new PrinterDirector;
	varDirector = new VarDirector;
	iniDirector = new IniDirector;
	nodeDirector = new NodeDirector;
	mainWindow = new MainWindow( );
	if( printerDirector->init( ) == false )
		return false;
	if( varDirector->init( ) == false )
		return false;
	if( iniDirector->init( ) == false )
		return false;
	if( nodeDirector->init( ) == false )
		return false;
	if( mainWindow->init( ) == false )
		return false;
	return true;
}
bool Application::setVar( const QString &var_key, const std::vector< uint8_t > &var_value ) {
	return iniDirector->setVar( var_key, var_value );
}
bool Application::getVar( const QString &result_var_key, std::vector< uint8_t > &result_var_value ) {
	return iniDirector->getVar( result_var_key, result_var_value );
}
bool Application::removeVar( const QString &result_var_key ) {
	return iniDirector->removeVar( result_var_key );
}
bool Application::synchronousFileToVar( ) {
	return iniDirector->synchronousFileToVar( iniSaveFilePathName );
}
bool Application::synchronousVarToFile( ) const {
	return iniDirector->synchronousVarToFile( iniSaveFilePathName );
}
void Application::clearVar( ) {
	iniDirector->clearVar( );
}
bool Application::createFile( const QString &create_file_path_name ) const {
	QFileInfo createFilePath( create_file_path_name );
	if( createFilePath.exists( ) ) {
		if( createFilePath.isFile( ) )
			return true;
		QDir removeDir;
		if( removeDir.remove( create_file_path_name ) == false )
			return false;
		QFile createFile( create_file_path_name );
		if( createFile.open( QIODeviceBase::NewOnly ) == false )
			return false;
		return true;
	}
	auto dir = createFilePath.dir( );
	auto absolutePath = dir.absolutePath( );
	if( dir.mkpath( absolutePath ) == false )
		return false;
	QFile createFile( create_file_path_name );
	if( createFile.open( QIODeviceBase::NewOnly ) == false )
		return false;
	return true;
}
bool Application::removeFile( const QString &remove_file_path_name ) const {
	QFileInfo removeFilePathInfo( remove_file_path_name );
	if( removeFilePathInfo.exists( ) == false )
		return true;
	if( removeFilePathInfo.isDir( ) == true )
		return false;
	QDir removePath;
	if( removePath.remove( remove_file_path_name ) == false )
		return false;
	return true;
}
bool Application::createDir( const QString &create_file_path_name ) const {
	QFileInfo createDirPathInfo( create_file_path_name );
	if( createDirPathInfo.exists( ) ) {
		if( createDirPathInfo.isDir( ) )
			return true;
		QDir createFilePath;
		if( createFilePath.remove( create_file_path_name ) == false )
			return false;
		if( createFilePath.mkdir( create_file_path_name ) == false )
			return false;
		return true;
	}
	QDir createDirPath( create_file_path_name );
	if( createDirPath.mkpath( create_file_path_name ) == false )
		return false;
	return true;
}
bool Application::removeDir( const QString &remove_file_path_name ) const {
	QFileInfo removeFilePathInfo( remove_file_path_name );
	if( removeFilePathInfo.exists( ) == false )
		return true;
	if( removeFilePathInfo.isFile( ) == true )
		return false;
	QDir removePath;
	if( removePath.remove( remove_file_path_name ) == false )
		return false;
	return true;
}
bool Application::hasFile( const QString &check_file_path_name ) const {
	QFileInfo checkFilePathInfo( check_file_path_name );
	if( checkFilePathInfo.exists( ) == false )
		return false;
	if( checkFilePathInfo.isFile( ) == false )
		return false;
	return true;
}
bool Application::hasDir( const QString &check_dir_path_name ) const {
	QFileInfo checkFilePathInfo( check_dir_path_name );
	if( checkFilePathInfo.exists( ) == false )
		return false;
	if( checkFilePathInfo.isDir( ) == false )
		return false;
	return true;
}
bool Application::getPathHasFileInfo( const QString &check_dir_path_name, QFileInfo &result_file_info ) const {
	result_file_info.setFile( check_dir_path_name );
	if( result_file_info.exists( ) )
		return true;
	auto dir = result_file_info.dir( );
	do {
		result_file_info.setFile( dir.absolutePath( ) );
		if( result_file_info.exists( ) )
			return true;
		if( result_file_info.isRoot( ) )
			return false;
		dir = result_file_info.dir( );
	} while( true );
	return false;
}
bool Application::widgetMoveTargetDispyer( QWidget *move_widget, const size_t &displyer_index ) const {
	auto screenList = screens( );
	qsizetype screenCount = screenList.size( );
	if( screenCount <= displyer_index )
		return false;
	auto screenArrayPtr = screenList.data( );
	auto &targetScreen = screenArrayPtr[ displyer_index ];
	auto availableGeometry = targetScreen->availableGeometry( );
	auto widgetSize = move_widget->size( );
	int offsetX = availableGeometry.x( ) + ( availableGeometry.width( ) - widgetSize.width( ) ) / 2;
	int offsetY = availableGeometry.y( ) + ( availableGeometry.height( ) - widgetSize.height( ) ) / 2;
	move_widget->move( offsetX, offsetY );
	return true;
}
bool Application::widgetMoveTargetDispyer( const size_t &displyer_index ) const {
	return widgetMoveTargetDispyer( mainWindow, displyer_index );
}
bool Application::widgetAllMoveTargetDispyer( const size_t &displyer_index ) const {
	auto screenList = screens( );
	qsizetype screenCount = screenList.size( );
	if( screenCount <= displyer_index )
		return false;
	auto screenArrayPtr = screenList.data( );
	auto &targetScreen = screenArrayPtr[ displyer_index ];
	auto availableGeometry = targetScreen->availableGeometry( );

	int offsetX = availableGeometry.x( ) + ( availableGeometry.width( ) ) / 2;
	int offsetY = availableGeometry.y( ) + ( availableGeometry.height( ) ) / 2;

	std::vector< std::pair< QWidget *, bool > > result;
	auto widgetList = allWidgets( );
	qsizetype widgetCount = widgetList.size( );
	auto widgetArrayPtr = widgetList.data( );
	qsizetype index = 0;
	for( ; index < widgetCount; ++index )
		widgetArrayPtr[ index ]->move( offsetX - widgetArrayPtr[ index ]->width( ) / 2, offsetY - widgetArrayPtr[ index ]->height( ) / 2 );
	return true;
}
