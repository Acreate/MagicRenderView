#include "application.h"

#include <QDir>
#include <QResizeEvent>
#include <QScreen>
#include <qfile.h>
#include <qfileinfo.h>

#include <director/iniDirector.h>
#include <director/nodeDirector.h>
#include <director/printerDirector.h>
#include <director/varDirector.h>

#include <win/mainWindow.h>

Application *Application::instance = nullptr;
Application * Application::getInstancePtr( ) {
	return instance;
}

Application::Application( int &argc, char **argv, int i ) : QApplication( argc, argv, i ), mainWindow( nullptr ), iniDirector( nullptr ), varDirector( nullptr ), printerDirector( nullptr ), nodeDirector( nullptr ), appInitRunDataTime( nullptr ) {
}
Application::~Application( ) {
	if( synchronousWindowInfoToVar( ) == false )
		printerDirector->error( "窗口状态保存异常" );
	if( synchronousVarToFile( ) == false )
		printerDirector->error( "程序信息保存异常" );
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
	if( appInitRunDataTime )
		delete appInitRunDataTime;
}
bool Application::notify( QObject *object, QEvent *event ) {
	if( object == mainWindow ) {
		bool notify = QApplication::notify( object, event );
		auto type = event->type( );
		QWindowStateChangeEvent *windowStateChangeEvent;
		QResizeEvent *resizeEvent;
		QMoveEvent *moveEvent;
		switch( type ) {
			case QEvent::Resize :
				resizeEvent = static_cast< QResizeEvent * >( event );
				if( resizeEvent ) {
					mainWindowBuffSize = resizeEvent->oldSize( );
					mainWindowSize = resizeEvent->size( );
				}
				break;
			case QEvent::Move :

				moveEvent = static_cast< QMoveEvent * >( event );
				if( moveEvent ) {
					mainWindowBuffPoint = moveEvent->oldPos( );
					mainWindowPoint = moveEvent->pos( );
				}
				break;
			case QEvent::WindowStateChange :
				windowStateChangeEvent = static_cast< QWindowStateChangeEvent * >( event );
				if( windowStateChangeEvent ) {
					auto currentWindowStates = mainWindow->windowState( );
					mainWindowState = windowStateChangeEvent->oldState( );
					if( currentWindowStates == Qt::WindowMaximized && mainWindowState == Qt::WindowNoState ) {
						mainWindowSize = mainWindowBuffSize;
						mainWindowPoint = mainWindowBuffPoint;
					}
				}
				break;

		}

		return notify;
	}
	return QApplication::notify( object, event );
}

bool Application::event( QEvent *event ) {
	return QApplication::event( event );

}
bool Application::init( ) {
	Application::instance = this;
	if( appInitRunDataTime == nullptr )
		appInitRunDataTime = new QDateTime;
	*appInitRunDataTime = QDateTime::currentDateTime( );
	auto currentApplcationDirPath = applicationDirPath( );
	auto appName = applicationName( );
	iniSaveFilePathName = currentApplcationDirPath + "/settings/" + appName + ".status";
	QFileInfo filePermission( iniSaveFilePathName );
	iniSaveFilePathName = filePermission.absoluteFilePath( );
	if( createFile( iniSaveFilePathName ) == false )
		return false;
	if( getPathHasFileInfo( iniSaveFilePathName, filePermission ) == false )
		return false;
	if( filePermission.isWritable( ) == false || filePermission.isReadable( ) == false )
		return false;
	logSaveFilePathName = currentApplcationDirPath + "/logs/" +
		appName + appInitRunDataTime->toString( "! yyyy_MM_dd hh_mm_s.z" ) + ".log";
	filePermission.setFile( logSaveFilePathName );
	logSaveFilePathName = filePermission.absoluteFilePath( );
	removeFile( logSaveFilePathName );
	if( createFile( logSaveFilePathName ) == false )
		return false;
	if( getPathHasFileInfo( logSaveFilePathName, filePermission ) == false )
		return false;
	if( filePermission.isWritable( ) == false || filePermission.isReadable( ) == false )
		return false;

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
	if( synchronousFileToVar( ) == false )
		return false;
	if( synchronousVarToWindowInfo( ) == false )
		return false;

	return true;
}
bool Application::setVar( const QString &var_key, const std::vector< uint8_t > &var_value ) const {
	return iniDirector->setVar( var_key, var_value );
}
bool Application::getVar( const QString &result_var_key, std::vector< uint8_t > &result_var_value ) const {
	return iniDirector->getVar( result_var_key, result_var_value );
}
bool Application::removeVar( const QString &result_var_key ) const {
	return iniDirector->removeVar( result_var_key );
}
bool Application::synchronousFileToVar( ) const {
	return iniDirector->synchronousFileToVar( iniSaveFilePathName );
}
bool Application::synchronousVarToFile( ) const {
	return iniDirector->synchronousVarToFile( iniSaveFilePathName );
}
bool Application::synchronousWindowInfoToVar( ) const {
	if( mainWindow == nullptr )
		return false;
	VarDirector director;
	if( director.init( ) == false )
		return false;
	std::vector< uint8_t > *data;
	if( director.create( data ) == false )
		return false;
	int64_t *int64Value;
	if( director.create( int64Value ) == false )
		return false;

	*int64Value = 1;
	if( director.toVector( int64Value, *data ) == false )
		return false;
	setVar( "!Application::synchronousWindowInfoToVar", *data );

	*int64Value = mainWindowSize.width( );
	if( director.toVector( int64Value, *data ) == false )
		return false;
	setVar( "width", *data );

	*int64Value = mainWindowSize.height( );;
	if( director.toVector( int64Value, *data ) == false )
		return false;
	setVar( "height", *data );

	*int64Value = mainWindowPoint.x( );
	if( director.toVector( int64Value, *data ) == false )
		return false;
	setVar( "x", *data );

	*int64Value = mainWindowPoint.y( );
	if( director.toVector( int64Value, *data ) == false )
		return false;
	setVar( "y", *data );
	// 窗口状态
	QByteArray mainWindowStateArray = mainWindow->saveState( );
	qsizetype newCount = mainWindowStateArray.size( );
	data->resize( newCount );
	auto dataArrayPtr = data->data( );
	char *sourceArrayPtr = mainWindowStateArray.data( );

	qsizetype index = 0;
	for( ; index < newCount; ++index )
		dataArrayPtr[ index ] = sourceArrayPtr[ index ];
	setVar( "@saveState", *data );

	// 显示状态
	Qt::WindowStates windowShowStates = mainWindow->windowState( );
	*int64Value = windowShowStates.toInt( );
	if( director.toVector( int64Value, *data ) == false )
		return false;
	setVar( "#windowState", *data );

	return true;
}
bool Application::synchronousVarToWindowInfo( ) {
	VarDirector director;
	if( director.init( ) == false )
		return false;
	std::vector< uint8_t > *data;
	if( director.create( data ) == false )
		return false;
	int64_t *int64Value;
	if( director.create( int64Value ) == false )
		return false;
	size_t userCount;
	uint8_t *dataArrayPtr;
	void *converVarPtr = int64Value;
	size_t dataArrayCount;

	getVar( "!Application::synchronousWindowInfoToVar", *data );
	dataArrayPtr = data->data( );
	dataArrayCount = data->size( );
	if( dataArrayPtr == nullptr || dataArrayCount == 0 )
		return true; // 未存在匹配的存储标识

	getVar( "width", *data );
	dataArrayPtr = data->data( );
	dataArrayCount = data->size( );
	if( director.toVar( userCount, dataArrayPtr, dataArrayCount, converVarPtr ) == false )
		return false;
	mainWindowSize.setWidth( *int64Value );

	getVar( "height", *data );
	dataArrayPtr = data->data( );
	dataArrayCount = data->size( );
	if( director.toVar( userCount, dataArrayPtr, dataArrayCount, converVarPtr ) == false )
		return false;
	mainWindowSize.setHeight( *int64Value );

	mainWindow->resize( mainWindowSize );

	getVar( "x", *data );
	dataArrayPtr = data->data( );
	dataArrayCount = data->size( );
	if( director.toVar( userCount, dataArrayPtr, dataArrayCount, converVarPtr ) == false )
		return false;
	mainWindowPoint.setX( *int64Value );

	getVar( "y", *data );
	dataArrayPtr = data->data( );
	dataArrayCount = data->size( );
	if( director.toVar( userCount, dataArrayPtr, dataArrayCount, converVarPtr ) == false )
		return false;
	mainWindowPoint.setY( *int64Value );

	mainWindow->move( mainWindowPoint );

	getVar( "#windowState", *data );
	if( director.toVar( userCount, dataArrayPtr, dataArrayCount, converVarPtr ) == false )
		return false;
	Qt::WindowStates state( *int64Value );
	mainWindow->setWindowState( state );

	getVar( "@saveState", *data );
	dataArrayPtr = data->data( );
	dataArrayCount = data->size( );
	QByteArray mainWindowState;
	mainWindowState.resize( dataArrayCount );
	auto targetDataPtr = mainWindowState.data( );
	userCount = 0;
	for( ; userCount < dataArrayCount; ++userCount )
		targetDataPtr[ userCount ] = dataArrayPtr[ userCount ];
	mainWindow->restoreState( mainWindowState );

	return true;
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
