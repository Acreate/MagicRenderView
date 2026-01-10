#include "application.h"

#include <QDir>
#include <QMetaEnum>
#include <QResizeEvent>
#include <QScreen>
#include <qfileinfo.h>

#include <director/iniDirector.h>
#include <director/nodeDirector.h>
#include <director/printerDirector.h>
#include <director/varDirector.h>

#include <win/mainWindow.h>

#include "../director/appDirector.h"
#include "../director/builderDirector.h"
#include "../director/editorDirector.h"
#include "../director/menuDirector.h"
#include "../director/nodeInfoEditorDirector.h"
#include "../srack/srackInfo.h"

#include "../tools/path.h"

Application *Application::instance = nullptr;
Application * Application::getInstancePtr( ) {
	return instance;
}

Application::Application( int &argc, char **argv, int i ) : QApplication( argc, argv, i ) {
	Application::instance = this;
	printerDirector = new PrinterDirector;
	varDirector = new VarDirector;
	iniDirector = new IniDirector;
	nodeDirector = new NodeDirector;
	menuDirector = new MenuDirector;
	appDirector = new AppDirector;
	editorDirector = new EditorDirector;
	mainWindow = new MainWindow( );
	builderDirector = new BuilderDirector;
	nodeInfoEditorDirector = new NodeInfoEditorDirector;
	appInitRunDataTime = new QDateTime;
}
Application::~Application( ) {
	if( synchronousWindowInfoToVar( ) == false )
		printerDirector->error( "窗口状态保存异常", Create_SrackInfo( ) );
	delete nodeInfoEditorDirector;
	delete builderDirector;
	delete menuDirector;
	delete appDirector;
	delete editorDirector;
	delete mainWindow;
	delete nodeDirector;
	if( synchronousVarToFile( ) == false )
		printerDirector->error( "程序信息保存异常", Create_SrackInfo( ) );
	delete iniDirector;
	delete varDirector;
	delete printerDirector;
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
	*appInitRunDataTime = QDateTime::currentDateTime( );
	auto currentApplcationDirPath = applicationDirPath( );
	auto appName = applicationName( );
	iniSaveFilePathName = currentApplcationDirPath + "/settings/" + appName + ".status";
	QFileInfo filePermission( iniSaveFilePathName );
	iniSaveFilePathName = filePermission.absoluteFilePath( );
	if( path::createFile( iniSaveFilePathName ) == false )
		return false;
	if( path::getPathHasFileInfo( iniSaveFilePathName, filePermission ) == false )
		return false;
	if( filePermission.isWritable( ) == false || filePermission.isReadable( ) == false )
		return false;
	// logSaveFilePathName = currentApplcationDirPath + "/logs/" + appName + appInitRunDataTime->toString( "!yyyy_MM_dd.hh_mm" ) + ".log";
	logSaveFilePathName = currentApplcationDirPath + "/logs/" + appName + appInitRunDataTime->toString( tr( "!yyyy_MM_dd.log" ) );
	filePermission.setFile( logSaveFilePathName );
	logSaveFilePathName = filePermission.absoluteFilePath( );
	path::removeFile( logSaveFilePathName );
	if( path::createFile( logSaveFilePathName ) == false )
		return false;
	if( path::getPathHasFileInfo( logSaveFilePathName, filePermission ) == false )
		return false;
	if( filePermission.isWritable( ) == false || filePermission.isReadable( ) == false )
		return false;

	if( printerDirector->init( ) == false )
		return false;
	if( varDirector->init( ) == false )
		return false;
	if( iniDirector->init( ) == false )
		return false;
	if( synchronousFileToVar( ) == false )
		return false;
	if( appDirector->init( ) == false )
		return false;
	if( menuDirector->init( ) == false )
		return false;
	if( nodeDirector->init( ) == false )
		return false;
	if( builderDirector->init( ) == false )
		return false;
	applicationMenuStack = menuDirector->getApplicationMenuStack( );
	if( applicationMenuStack == nullptr )
		return false;
	if( mainWindow->init( ) == false )
		return false;
	if( synchronousVarToWindowInfo( ) == false )
		return false;
	if( editorDirector->init( ) == false )
		return false;
	if( nodeInfoEditorDirector->init( ) == false )
		return false;
	mainWindow->show( );
	if( mainWindow->isHidden( ) )
		return false;
	mainWindow->raise( );
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
	auto metaEnum = QMetaEnum::fromType< Qt::WindowStates >( );
	Qt::WindowStates state = static_cast< Qt::WindowStates >( metaEnum.value( *int64Value ) );
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
