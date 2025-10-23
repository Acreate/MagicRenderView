#include "mainWindow.h"

#include <QDockWidget>
#include <QFileDialog>
#include <QMenuBar>
#include <QMouseEvent>
#include <QShortcut>

#include <qt/application/application.h>
#include <qt/tools/tools.h>
#include <qt/widgets/mainScrollAreaWidget.h>
#include <qt/widgets/mainWidget.h>

#include <qt/node/director/nodeDirector.h>

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {

	setWindowToIndexScreenCentre( 0 );

	appInstance = Application::getApplicationInstancePtr( );
	keyFirst = "Application/MainWindow";
	savefilePathKey = "saveFilePath";

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

	mainScrollArea = new MainScrollAreaWidget( this );
	mainWidget = new MainWidget( mainScrollArea );
	setCentralWidget( mainScrollArea );

	auto extendState = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "extendState" ), this->saveState( ) );
	this->restoreState( extendState.toByteArray( ) );

	mainMenuBar = menuBar( );
	if( mainMenuBar == nullptr )
		mainMenuBar = new QMenuBar( this );

	QMenu *currentMenu = new QMenu( "文件", this );
	mainMenuBar->addMenu( currentMenu );

	QAction *currentAction;

	currentAction = currentMenu->addAction( "保存..." );
	connect( currentAction, &QAction::triggered, [this]( ) {
		normalSave( );
	} );

	currentAction = currentMenu->addAction( "另存为..." );
	connect( currentAction, &QAction::triggered, [this]( ) {
		overSave( );
	} );

	currentAction = currentMenu->addAction( "加载..." );
	connect( currentAction, &QAction::triggered, this, &MainWindow::normalLoadFile );

	currentMenu = new QMenu( "配置", this );
	mainMenuBar->addMenu( currentMenu );
	currentMenu = currentMenu->addMenu( "重启&&退出" );
	currentAction = currentMenu->addAction( "重启" );
	connect( currentAction, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->resetApp( );
	} );
	currentAction = currentMenu->addAction( "退出" );
	connect( currentAction, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->quitApp( );
	} );

	currentMenu = mainMenuBar->addMenu( "快速菜单" );

	currentAction = currentMenu->addAction( "快速保存" );
	connect( currentAction, &QAction::triggered, this, &MainWindow::quickSave );

	currentAction = currentMenu->addAction( "快速加载" );
	connect( currentAction, &QAction::triggered, this, &MainWindow::quickLoadFile );

	QShortcut *shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_C ), this );
	connect( shortcut, &QShortcut::activated, [this]( ) {
		mainWidget->copyNodeItemActionInfo( );
	} );
	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_V ), this );
	connect( shortcut, &QShortcut::activated, [this]( ) {
		mainWidget->pasteNodeItemActionInfo( );
	} );
	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_S ), this );
	connect( shortcut, &QShortcut::activated, [this]( ) {
		if( currentSaveFilePath.isEmpty( ) )
			overSave( );
		else
			normalSave( );
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
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "extendState" ), this->saveState( ) );
	appInstance->syncAppValueIniFile( );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::overSave( ) {
	QString workPath = QDir::currentPath( );
	QString normalKey = appInstance->normalKeyAppendEnd( keyFirst, this, savefilePathKey );
	workPath = appInstance->getAppIniValue( normalKey, workPath ).toString( );
	QString saveFileName = QFileDialog::getSaveFileName( this, "文件保存", workPath, "魅力渲染 (*.mr *.mrv *.magicrender *.magicrenderview)" );
	if( saveFileName.isEmpty( ) )
		return;
	qsizetype lastIndexOf = saveFileName.lastIndexOf( "/" );
	auto fileName = saveFileName.mid( lastIndexOf + 1 );
	lastIndexOf = fileName.lastIndexOf( "." );
	if( lastIndexOf == -1 )
		saveFileName.append( ".mr" );

	std_vector< uint8_t > saveBin;
	if( appInstance->getNodeDirector( )->toDataBin( saveBin ) == 0 ) {
		tools::debug::printError( "保存异常，请检查保存功能" );
		return;
	}

	QFile file( saveFileName );
	if( file.open( QIODeviceBase::Truncate | QIODeviceBase::WriteOnly ) ) {
		file.write( ( const char * ) saveBin.data( ), saveBin.size( ) );
		currentSaveFilePath = saveFileName;
		appInstance->syncAppValueIniFile( );
		appInstance->setAppIniValue( normalKey, saveFileName );
		appInstance->syncAppValueIniFile( );
		return;
	}
}
void MainWindow::normalSave( ) {
	if( currentSaveFilePath.isEmpty( ) ) {
		overSave( );
		return;
	}
	std_vector< uint8_t > saveBin;
	if( appInstance->getNodeDirector( )->toDataBin( saveBin ) == 0 ) {
		tools::debug::printError( "保存异常，请检查保存功能" );
		return;
	}

	QFile file( currentSaveFilePath );
	if( file.open( QIODeviceBase::Truncate | QIODeviceBase::WriteOnly ) ) {
		file.write( ( const char * ) saveBin.data( ), saveBin.size( ) );
		return;
	}
}
void MainWindow::overLoadFile( ) {
	QString workPath = QDir::currentPath( );
	QString normalKey = appInstance->normalKeyAppendEnd( keyFirst, this, savefilePathKey );
	workPath = appInstance->getAppIniValue( normalKey, workPath ).toString( );
	if( QFileInfo( workPath ).isDir( ) ) {
		normalLoadFile( );
	}
	QFile file( workPath );
	if( file.open( QIODeviceBase::ReadOnly | QIODeviceBase::ExistingOnly ) ) {
		QByteArray byteArray = file.readAll( );
		char *sourceDataPtr = byteArray.data( );
		size_t sourceDataCount = byteArray.size( );
		size_t loadDataBinCount = appInstance->getNodeDirector( )->loadDataBin( ( const uint8_t * ) sourceDataPtr, sourceDataCount );
		if( loadDataBinCount == 0 ) {
			tools::debug::printError( "文件异常，非程序存档，请检查文件内容是否正确" );
			return;
		}
		return;
	}
}
void MainWindow::normalLoadFile( ) {
	QString workPath = QDir::currentPath( );
	QString normalKey = appInstance->normalKeyAppendEnd( keyFirst, this, savefilePathKey );
	workPath = appInstance->getAppIniValue( normalKey, workPath ).toString( );
	QString loadFileName = QFileDialog::getOpenFileName( this, "文件保存", workPath, "魅力渲染 (*.mr *.mrv *.magicrender *.magicrenderview);;任意文件 (*.*);;其他文件 (*)" );
	if( loadFileName.isEmpty( ) ) {
		tools::debug::printError( "文件异常，非正常文件，空或者没有读取权限" );
		return;
	}
	appInstance->setAppIniValue( normalKey, loadFileName );
	QFile file( loadFileName );
	if( file.open( QIODeviceBase::ReadOnly | QIODeviceBase::ExistingOnly ) ) {
		QByteArray byteArray = file.readAll( );
		char *sourceDataPtr = byteArray.data( );
		size_t sourceDataCount = byteArray.size( );
		size_t loadDataBinCount = appInstance->getNodeDirector( )->loadDataBin( ( const uint8_t * ) sourceDataPtr, sourceDataCount );
		if( loadDataBinCount == 0 ) {
			tools::debug::printError( "文件异常，非程序存档，请检查文件内容是否正确" );
			return;
		}
		currentSaveFilePath = loadFileName;
		return;
	}
}
void MainWindow::ensureMainWidgetVisibleToItemNode( const NodeItem *targetItemNode ) {
	mainWidget->ensureVisibleToItemNode( targetItemNode );
}
void MainWindow::updateMainWidgetSupport( ) {
	//mainWidget->updateSupport( );
}
size_t MainWindow::objMainWidgetToBin( std_vector< uint8_t > &result_vector ) const {
	//return mainWidget->objToBin( result_vector );
	return 0;
}
size_t MainWindow::loadMainWidgetBin( const uint8_t *bin_data_ptr, const size_t &bin_data_count ) {
	//return mainWidget->loadBin( bin_data_ptr, bin_data_count );
	return 0;
}
void MainWindow::quickSave( ) {
	QString workPath = QDir::currentPath( );
	
	QString normalKey = appInstance->normalKeyAppendEnd( keyFirst, this, savefilePathKey );
	workPath = appInstance->getAppIniValue( normalKey, workPath ).toString( );

	qsizetype lastIndexOf = workPath.lastIndexOf( "/" );
	auto fileName = workPath.mid( lastIndexOf + 1 );
	lastIndexOf = fileName.lastIndexOf( "." );
	if( lastIndexOf == -1 )
		workPath.append( ".mr" );
	appInstance->setAppIniValue( normalKey, workPath );
	std_vector< uint8_t > saveBin;
	if( appInstance->getNodeDirector( )->toDataBin( saveBin ) == 0 ) {
		tools::debug::printError( "保存异常，请检查保存功能" );
		return;
	}

	QFile file( workPath );
	if( file.open( QIODeviceBase::Truncate | QIODeviceBase::WriteOnly ) ) {
		file.write( ( const char * ) saveBin.data( ), saveBin.size( ) );
		return;
	}
}
void MainWindow::quickLoadFile( ) {
	overLoadFile(  );
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
void MainWindow::closeEvent( QCloseEvent *event ) {
	QMainWindow::closeEvent( event );
	appInstance->quitApp( );
}
void MainWindow::createNewItemWidget( ItemWidget *generate_new_item_widget, const QRect &contents_rect, const QRect &contents_item_widget_united_rect ) {
	QPoint point = contents_rect.bottomRight( );
	mainScrollArea->ensureVisible( point.x( ), point.y( ) );
}
