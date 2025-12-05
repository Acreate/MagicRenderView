#include "mainWindow.h"

#include <QMenu>
#include <QFileDialog>
#include <QMouseEvent>
#include <QToolBar>

#include "../app/application.h"

#include "../director/nodeDirector.h"

#include "../tools/path.h"

#include "../widget/drawLinkWidget.h"
#include "../widget/drawNodeWidget.h"
#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"

MainWindow::MainWindow( ) : mainWidgetScrollArea( nullptr ) {
	hide( );
	mainWidgetScrollArea = new MainWidgetScrollArea( this );
	setCentralWidget( mainWidgetScrollArea );
	mainWidget = mainWidgetScrollArea->getMainWidget( );

	toolBar = new QToolBar( this );
	toolBar->setObjectName( tr( "主要工具栏" ) );
}
bool MainWindow::init( ) {
	if( mainWidget->init( ) == false )
		return false;

	addToolBar( Qt::TopToolBarArea, toolBar );
	toolBar->setFloatable( false );
	toolBar->setAllowedAreas( Qt::TopToolBarArea );
	toolBar->setMovable( false );
	instancePtr = Application::getInstancePtr( );
	nodeDirector = instancePtr->getNodeDirector( );
	drawNodeWidget = mainWidget->getDrawNodeWidget( );
	drawLinkWidget = mainWidget->getDrawLinkWidget( );
	saveFileDirPath = instancePtr->applicationDirPath( );
	toolBar->clear( );
	auto addAction = toolBar->addAction( tr( "保存..." ) );
	connect( addAction, &QAction::triggered, this, &MainWindow::savePorjectToFile );
	addAction = toolBar->addAction( tr( "加载..." ) );
	connect( addAction, &QAction::triggered, this, &MainWindow::loadPorjectAtFile );
	return true;
}
MainWindow::~MainWindow( ) {
	emit release_signal( this );
	delete mainWidgetScrollArea;
}
void MainWindow::savePorjectToFile( ) {
	auto openFileName = QFileDialog::getSaveFileName( this, tr( "保存文件" ), saveFileDirPath, tr( "魔术窗口 (*.mrv)" ) );
	if( openFileName.isEmpty( ) )
		return;
	size_t dataCount = 0;
	std::vector< uint8_t > dataVector;
	if( nodeDirector->toUint8VectorData( dataVector ) == false || dataCount == 0 )
		return;
	QFileInfo fileInfo( openFileName );
	QString absoluteFilePath = fileInfo.absoluteFilePath( );
	if( fileInfo.exists( ) == false )
		if( path::createFile( absoluteFilePath ) == false )
			return;
	saveFileDirPath = fileInfo.dir( ).absolutePath( );
	QFile file( absoluteFilePath );
	if( file.open( QIODeviceBase::WriteOnly | QIODeviceBase::Truncate ) == false )
		return;
	auto data = dataVector.data( );
	file.write( ( char * ) data, dataCount );
}
void MainWindow::loadPorjectAtFile( ) {
	auto openFileName = QFileDialog::getOpenFileName( this, tr( "保存文件" ), saveFileDirPath, tr( "魔术窗口 (*.mrv)" ) );
	if( openFileName.isEmpty( ) )
		return;

	QFileInfo fileInfo( openFileName );
	if( fileInfo.exists( ) == false )
		return;
	saveFileDirPath = fileInfo.dir( ).absolutePath( );
	QFile file( fileInfo.absoluteFilePath( ) );
	if( file.open( QIODeviceBase::ReadOnly ) == false )
		return;
	auto byteArray = file.readAll( );
	size_t count = byteArray.size( );
	if( count == 0 )
		return;

	auto data = byteArray.data( );
	count = count * ( sizeof( data[ 0 ] ) / sizeof( uint8_t ) );
	size_t dataCount = 0;

	if( nodeDirector->formUint8ArrayData( dataCount, ( uchar * ) data, count ) == false )
		return;
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
	QMainWindow::mouseReleaseEvent( event );

}
void MainWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );

}
bool MainWindow::event( QEvent *event ) {
	return QMainWindow::event( event );
}
