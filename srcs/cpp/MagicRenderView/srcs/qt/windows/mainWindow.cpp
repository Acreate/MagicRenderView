#include "mainWindow.h"

#include <QDockWidget>
#include <QFileDialog>
#include <QToolBar>
#include <QMenuBar>
#include <QMouseEvent>
#include <QShortcut>

#include <qt/application/application.h>
#include <qt/node/director/nodeDirector.h>
#include <qt/tools/tools.h>
#include <qt/widgets/mainWidget/mainScrollAreaWidget.h>
#include <qt/widgets/mainWidget/mainWidget.h>

#include "../node/director/nodeItemBuilderObj.h"

void MainWindow::initMenuActions( ) {

	saveAction = new QAction( tr( "保存..." ), this );
	connect( saveAction, &QAction::triggered, [this]( ) {
		normalSave( );
	} );
	saveAsAction = new QAction( tr( "另存为..." ), this );
	connect( saveAsAction, &QAction::triggered, [this]( ) {
		overSave( );
	} );

	loadAction = new QAction( tr( "加载..." ), this );
	connect( loadAction, &QAction::triggered, this, &MainWindow::normalLoadFile );

	resetAppAction = new QAction( tr( "重启" ), this );
	connect( resetAppAction, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->resetApp( );
	} );

	quitAppAction = new QAction( tr( "退出" ), this );
	connect( quitAppAction, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->quitApp( );
	} );
	builderNodeItemAction = new QAction( tr( "编译" ), this );
	connect( builderNodeItemAction, &QAction::triggered, [this]( ) {
		if( nodeItemBuilderObj )
			delete nodeItemBuilderObj;
		nodeItemBuilderObj = Application::getApplicationInstancePtr( )->getNodeDirector( )->builderNodeItem( );

	} );
	resetRunNodeItemAction = new QAction( tr( "重置编译状态" ), this );
	runDisposableAllNodeItemAction = new QAction( tr( "全部运行" ), this );
	runListAllNodeItemAction = new QAction( tr( "链式运行" ), this );
	runNodeItemAllNodeItemAction = new QAction( tr( "节点式运行" ), this );

	quickSaveCurrentAction = new QAction( tr( "快速保存" ), this );
	connect( quickSaveCurrentAction, &QAction::triggered, this, &MainWindow::quickSave );

	quickLoadCurrentAction = new QAction( tr( "快速加载" ), this );
	connect( quickLoadCurrentAction, &QAction::triggered, this, &MainWindow::quickLoadFile );

}
void MainWindow::initShortcut( ) {
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
void MainWindow::initMenuBar( ) {

	mainMenuBar = menuBar( );
	if( mainMenuBar == nullptr )
		mainMenuBar = new QMenuBar( this );

	QMenu *currentMenu = new QMenu( tr( "文件" ), this );
	mainMenuBar->addMenu( currentMenu );
	currentMenu->addAction( saveAction );
	currentMenu->addAction( saveAsAction );
	currentMenu->addAction( loadAction );

	currentMenu = new QMenu( tr( "配置" ), this );
	mainMenuBar->addMenu( currentMenu );
	currentMenu = currentMenu->addMenu( tr( "重启&&退出" ) );
	currentMenu->addAction( resetAppAction );
	currentMenu->addAction( quitAppAction );

	currentMenu = new QMenu( tr( "项目" ), this );
	mainMenuBar->addMenu( currentMenu );
	currentMenu->addAction( builderNodeItemAction );

	currentMenu = mainMenuBar->addMenu( tr( "快速菜单" ) );
	currentMenu->addAction( quickSaveCurrentAction );
	currentMenu->addAction( quickLoadCurrentAction );

}
void MainWindow::initToolBar( ) {
	QString title = tr( "编译工具" );
	QToolBar *toolBar = addToolBar( title );
	toolBar->setObjectName( title );
	toolBar->setAllowedAreas( Qt::TopToolBarArea );
	toolBar->setFloatable( false );
	toolBar->setMovable( false );
	toolBar->addAction( builderNodeItemAction );
	toolBar->addAction( runDisposableAllNodeItemAction );
	toolBar->addAction( runListAllNodeItemAction );
	toolBar->addAction( runNodeItemAllNodeItemAction );
}
void MainWindow::initIcons( ) {
	builderNodeItemAction->setIcon( QIcon( ":/appIcon/builder_action.png" ) );
}
void MainWindow::initMainWindowShowStatus( ) {
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
}
MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {
	nodeItemBuilderObj = nullptr;
	setWindowToIndexScreenCentre( 0 );

	appInstance = Application::getApplicationInstancePtr( );
	keyFirst = "Application/MainWindow";
	savefilePathKey = "saveFilePath";
	initMenuActions( );
	initMenuBar( );
	initShortcut( );
	initToolBar( );
	initIcons( );
	initMainWindowShowStatus( );
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
	delete nodeItemBuilderObj;
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
	overLoadFile( );
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
