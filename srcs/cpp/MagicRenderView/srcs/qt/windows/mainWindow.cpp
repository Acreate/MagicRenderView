#include "mainWindow.h"

#include <qguiapplication.h>
#include <QMenuBar>
#include <QProcess>
#include <QScrollBar>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPushButton>

#include <qt/tools/tools.h>

#include <qt/application/application.h>

#include <qt/widgets/mainWidget.h>

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {

	setWindowToIndexScreenCentre( 0 );

	appInstance = Application::getApplicationInstancePtr( );
	keyFirst = "Application/MainWindow";

	QSize size = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "size" ), this->contentsRect( ).size( ) ).toSize( );
	setBaseSize( size );

	Qt::WindowStates windowStates( appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "windowState" ), this->windowState( ).toInt( ) ).toInt( ) );
	setWindowState( windowStates );
	if( windowStates == Qt::WindowNoState || windowStates == Qt::WindowActive )
		makePos = true;
	else
		makePos = false;

	QPoint point = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "pos" ), this->pos( ) ).toPoint( );
	move( point );
	oldPos = buffPos = point;

	mainScrollArea = new QScrollArea( this );
	mainWidget = new MainWidget( mainScrollArea );
	setCentralWidget( mainScrollArea );

	mainMenuBar = menuBar( );
	if( mainMenuBar == nullptr )
		mainMenuBar = new QMenuBar( this );

	mainMenu = new QMenu( "应用", this );
	mainMenuBar->addMenu( mainMenu );

	QAction *action;
	
	mainMenu->addSeparator( );
	action = mainMenu->addAction( "保存..." );
	connect( action, &QAction::triggered, [this]( ) {
		QString workPath = QDir::currentPath( );
		QString normalKey = appInstance->normalKeyAppendEnd( keyFirst, this, "saveFilePath" );
		workPath = appInstance->getAppIniValue( normalKey, workPath ).toString( );
		QString saveFileName = QFileDialog::getSaveFileName( this, "文件保存", workPath, "魅力渲染 (*.mr *.mrv *.magicrender *.magicrenderview)" );
		if( saveFileName.isEmpty( ) )
			return;
		qsizetype lastIndexOf = workPath.lastIndexOf( "/" );
		auto fileName = workPath.mid( lastIndexOf + 1 );
		lastIndexOf = fileName.lastIndexOf( "." );
		if( lastIndexOf == -1 )
			saveFileName.append( ".mr" );
		appInstance->setAppIniValue( normalKey, workPath );
		std_vector< uint8_t > saveBin;
		if( mainWidget->objToBin( saveBin ) == 0 )
			return;

		QFile file( saveFileName );
		if( file.open( QIODeviceBase::Truncate | QIODeviceBase::WriteOnly ) ) {
			file.write( ( const char * ) saveBin.data( ), saveBin.size( ) );
			return;
		}
	} );

	action = mainMenu->addAction( "加载..." );
	connect( action, &QAction::triggered, [this]( ) {
		QString workPath = QDir::currentPath( );
		QString normalKey = appInstance->normalKeyAppendEnd( keyFirst, this, "loadFilePath" );
		workPath = appInstance->getAppIniValue( normalKey, workPath ).toString( );
		QString loadFileName = QFileDialog::getSaveFileName( this, "文件保存", workPath, "魅力渲染 (*.mr *.mrv *.magicrender *.magicrenderview);;任意文件 (*.*);;其他文件 (*)" );
		if( loadFileName.isEmpty( ) )
			return;
		appInstance->setAppIniValue( normalKey, workPath );
		QFile file( loadFileName );
		if( file.open( QIODeviceBase::ReadOnly | QIODeviceBase::ExistingOnly ) ) {
			QByteArray byteArray = file.readAll( );
			mainWidget->loadBin( byteArray );
			return;
		}
	} );
	
	mainMenu->addSeparator( );
	action = mainMenu->addAction( "重启" );
	connect( action, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->resetApp( );
	} );
	action = mainMenu->addAction( "退出" );
	connect( action, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->quitApp( );
	} );

}
MainWindow::~MainWindow( ) {
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "size" ), this->contentsRect( ).size( ) );
	Qt::WindowStates windowState = this->windowState( );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "windowState" ), windowState.toInt( ) );

	if( makePos )
		appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "pos" ), buffPos );
	else
		appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "pos" ), oldPos );
	appInstance->syncAppValueIniFile( );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::ensureMainWidgetVisibleToItemNode( const NodeItem *targetItemNode ) {
	mainWidget->ensureVisibleToItemNode( targetItemNode );
}
void MainWindow::updateMainWidgetSupport( ) {
	mainWidget->updateSupport( );
}
const std_vector< uint8_t > & MainWindow::getMainWidgetSupportBin( ) const {
	return mainWidget->getSupportBin( );
}
const std_vector< uint8_t > & MainWindow::getMainWidgetSupportNodeNmaeBin( ) const {
	return mainWidget->getSupportNodeNmaeBin( );
}
const std_vector< uint8_t > & MainWindow::getMainWidgetSupportVarTypeNameBin( ) const {
	return mainWidget->getSupportVarTypeNameBin( );
}
size_t MainWindow::objMainWidgetToBin( std_vector< uint8_t > &result_vector ) const {
	return mainWidget->objToBin( result_vector );
}
size_t MainWindow::loadMainWidgetBin( const uint8_t *bin_data_ptr, const size_t &bin_data_count ) {
	return mainWidget->loadBin( bin_data_ptr, bin_data_count );
}
void MainWindow::resizeEvent( QResizeEvent *resize_event ) {
	QMainWindow::resizeEvent( resize_event );
}
void MainWindow::changeEvent( QEvent *event ) {
	QMainWindow::changeEvent( event );
	QEvent::Type type = event->type( );
	switch( type ) {
		case QEvent::WindowStateChange :
			Qt::WindowStates state = windowState( );
			auto newStateFlag = state == Qt::WindowNoState || state == Qt::WindowActive;
			if( newStateFlag == false )
				makePos = false;
			else {
				makePos = true;
				oldPos = buffPos = this->pos( );
			}
			break;
	}
}

bool MainWindow::event( QEvent *event ) {
	QEvent::Type type = event->type( );
	QMoveEvent *widgetMove;
	QPoint point = this->pos( );
	bool eventResult;
	switch( type ) {
		case QEvent::Move :
			eventResult = QMainWindow::event( event );
			widgetMove = static_cast< QMoveEvent * >( event );
			if( widgetMove && makePos )
				buffPos = point;
			return eventResult;
	}
	return QMainWindow::event( event );
}
void MainWindow::mouseMoveEvent( QMouseEvent *event ) {
	QMainWindow::mouseMoveEvent( event );
}
void MainWindow::createNewItemWidget( ItemWidget *generate_new_item_widget, const QRect &contents_rect, const QRect &contents_item_widget_united_rect ) {
	QPoint point = contents_rect.bottomRight( );
	mainScrollArea->ensureVisible( point.x( ), point.y( ) );
}
