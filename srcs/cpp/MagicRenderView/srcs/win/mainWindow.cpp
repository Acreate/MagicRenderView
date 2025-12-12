#include "mainWindow.h"

#include <QShortcut>
#include <QMenu>
#include <QFileDialog>
#include <QMouseEvent>
#include <QToolBar>

#include "../app/application.h"

#include "../director/nodeDirector.h"
#include "../director/printerDirector.h"

#include "../srack/srackInfo.h"

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
	size_t count = shortcutVector.size( );
	auto shortcutArrayPtr = shortcutVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete shortcutArrayPtr[ index ];
	shortcutVector.clear( );

	addToolBar( Qt::TopToolBarArea, toolBar );
	toolBar->setFloatable( false );
	toolBar->setAllowedAreas( Qt::TopToolBarArea );
	toolBar->setMovable( false );
	instancePtr = Application::getInstancePtr( );
	nodeDirector = instancePtr->getNodeDirector( );
	printerDirector = instancePtr->getPrinterDirector( );
	drawNodeWidget = mainWidget->getDrawNodeWidget( );
	drawLinkWidget = mainWidget->getDrawLinkWidget( );
	saveFileDirPath = instancePtr->applicationDirPath( );
	toolBar->clear( );
	auto addAction = toolBar->addAction( tr( "保存..." ) );
	connect( addAction, &QAction::triggered, this, &MainWindow::savePorjectToFile );
	addAction = toolBar->addAction( tr( "加载..." ) );
	connect( addAction, &QAction::triggered, this, &MainWindow::loadPorjectAtFile );
	addAction = toolBar->addAction( tr( "放弃..." ) );
	connect( addAction, &QAction::triggered, this, &MainWindow::unDownloadPorjectAtFile );

	QShortcut *shortcut;
	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_S ), this );
	connect( shortcut, &QShortcut::activated, this, &MainWindow::savePorjectToFile );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_O ), this );
	connect( shortcut, &QShortcut::activated, this, &MainWindow::savePorjectToFile );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_C ), this );
	connect( shortcut, &QShortcut::activated, this, &MainWindow::copyNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_V ), this );
	connect( shortcut, &QShortcut::activated, this, &MainWindow::pasteNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_X ), this );
	connect( shortcut, &QShortcut::activated, this, &MainWindow::cutNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_Z ), this );
	connect( shortcut, &QShortcut::activated, this, &MainWindow::cancelNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::Key_Delete ), this );
	connect( shortcut, &QShortcut::activated, this, &MainWindow::deleteNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::Key_Backspace ), this );
	connect( shortcut, &QShortcut::activated, this, &MainWindow::deleteNodeInfo );
	shortcutVector.emplace_back( shortcut );

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
	size_t dataCount;
	std::vector< uint8_t > dataVector;
	if( nodeDirector->toUint8VectorData( dataVector ) == false ) {
		printerDirector->info( tr( "路径[%1]保存异常,数据量异常(%2)" ).arg( openFileName ).arg( dataVector.size( ) ), Create_SrackInfo( ) );
		return;
	}
	QFileInfo fileInfo( openFileName );
	QString absoluteFilePath = fileInfo.absoluteFilePath( );
	if( fileInfo.exists( ) == false )
		if( path::createFile( absoluteFilePath ) == false )
			return;
	saveFileDirPath = fileInfo.dir( ).absolutePath( );
	QFile file( absoluteFilePath );
	if( file.open( QIODeviceBase::WriteOnly | QIODeviceBase::Truncate ) == false ) {
		printerDirector->info( tr( "路径[%1]保存异常,文件打开异常" ).arg( openFileName ), Create_SrackInfo( ) );
		return;
	}
	auto data = dataVector.data( );
	dataCount = dataVector.size( );
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
	if( file.open( QIODeviceBase::ReadOnly ) == false ) {
		printerDirector->info( tr( "路径[%1]文件打开异常" ).arg( openFileName ), Create_SrackInfo( ) );
		return;
	}
	auto byteArray = file.readAll( );
	size_t count = byteArray.size( );
	if( count == 0 ) {
		printerDirector->info( tr( "路径[%1]文件读取异常，数据量为 0" ).arg( openFileName ), Create_SrackInfo( ) );
		return;
	}

	auto data = byteArray.data( );
	count = count * ( sizeof( data[ 0 ] ) / sizeof( uint8_t ) );
	size_t dataCount = 0;

	if( nodeDirector->formUint8ArrayData( dataCount, ( uchar * ) data, count ) == false ) {
		printerDirector->info( tr( "路径[%1]文件读取异常，数据无法进行还原节点" ).arg( openFileName ), Create_SrackInfo( ) );
		return;
	}

}
void MainWindow::unDownloadPorjectAtFile( ) {
	nodeDirector->init( );
}
void MainWindow::copyNodeInfo( ) {
	mainWidget->copySelectNodeInfo( );
}
void MainWindow::pasteNodeInfo( ) {
	mainWidget->pastePointNodeInfo( );
}
void MainWindow::cutNodeInfo( ) {
	mainWidget->cutSelectNodeInfo( );
}
void MainWindow::cancelNodeInfo( ) {
	mainWidget->cancelNodeInfo( );
}
void MainWindow::deleteNodeInfo( ) {
	mainWidget->deleteSelectNodeInfo( );
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
	QMainWindow::mouseReleaseEvent( event );
}
void MainWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
}
bool MainWindow::event( QEvent *event ) {
	bool runEventResult = QMainWindow::event( event );
	return runEventResult;
}
