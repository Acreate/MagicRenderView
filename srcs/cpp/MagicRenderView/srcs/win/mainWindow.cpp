#include "mainWindow.h"

#include <QShortcut>
#include <QMenu>
#include <QFileDialog>
#include <QMenuBar>
#include <QMouseEvent>
#include <QToolBar>

#include "../app/application.h"

#include "../director/nodeDirector.h"
#include "../director/printerDirector.h"
#include "../node/nodeInfo/nodeRunInfo.h"

#include "../srack/srackInfo.h"

#include "../tools/path.h"

#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"

MainWindow::MainWindow( ) : mainWidgetScrollArea( nullptr ) {

	//nodeRunBuilderObj = nullptr;
	instancePtr = nullptr;
	nodeDirector = nullptr;
	printerDirector = nullptr;
	saveFileDirPath = nullptr;

	hide( );

	mainWidgetScrollArea = new MainWidgetScrollArea( this );
	setCentralWidget( mainWidgetScrollArea );
	mainWidget = mainWidgetScrollArea->getMainWidget( );

	fileToolBar = new QToolBar( this );
	projectToolBar = new QToolBar( this );
	fileToolBar->setObjectName( tr( "主要工具栏" ) );
	projectToolBar->setObjectName( tr( "主要项目工具" ) );
	fileMenu = new QMenu( tr( "文件" ), this );
	projectMenu = new QMenu( tr( "项目" ), this );

	appMenuBar = menuBar( );
	if( appMenuBar == nullptr ) {
		appMenuBar = new QMenuBar( this );
		setMenuBar( appMenuBar );
	}
	appMenuBar->addMenu( fileMenu );
	appMenuBar->addMenu( projectMenu );

	addToolBar( Qt::TopToolBarArea, fileToolBar );
	fileToolBar->setFloatable( false );
	fileToolBar->setAllowedAreas( Qt::TopToolBarArea );
	fileToolBar->setMovable( true );

	addToolBar( Qt::TopToolBarArea, projectToolBar );
	projectToolBar->setFloatable( false );
	projectToolBar->setAllowedAreas( Qt::TopToolBarArea );
	projectToolBar->setMovable( true );

}
bool MainWindow::init( ) {
	if( mainWidget->init( ) == false )
		return false;
	/*size_t count = shortcutVector.size( );
	auto shortcutArrayPtr = shortcutVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete shortcutArrayPtr[ index ];
	shortcutVector.clear( );
	count = actionVector.size( );
	index = 0;
	auto actionArrayPtr = actionVector.data( );
	for( ; index < count; ++index )
		delete actionArrayPtr[ index ];
	actionVector.clear( );*/

	//if( nodeRunBuilderObj ) {
	//	nodeRunBuilderObj->clear( );
	//	nodeRunBuilderObj = nullptr;
	//}
	instancePtr = Application::getInstancePtr( );
	// 释放节点
	//if( nodeDirector ) {
	//	disconnect( nodeDirector, &NodeDirector::node_run_info_clear_signal, this, &MainWindow::node_run_info_clear_slot );
	//}
	nodeDirector = instancePtr->getNodeDirector( );
	//
	//connect( nodeDirector, &NodeDirector::node_run_info_clear_signal, this, &MainWindow::node_run_info_clear_slot );

	printerDirector = instancePtr->getPrinterDirector( );
	saveFileDirPath = instancePtr->applicationDirPath( );
	fileToolBar->clear( );
	projectToolBar->clear( );

	//auto addAction = new QAction( tr( "保存文件..." ), this );
	//connect( addAction, &QAction::triggered, this, &MainWindow::savePorjectToFile );
	//fileToolBar->addAction( addAction );
	//fileMenu->addAction( addAction );
	//actionVector.emplace_back( addAction );
	//addAction = new QAction( tr( "加载文件..." ), this );
	//connect( addAction, &QAction::triggered, this, &MainWindow::loadPorjectAtFile );
	//fileToolBar->addAction( addAction );
	//fileMenu->addAction( addAction );
	//actionVector.emplace_back( addAction );
	//addAction = new QAction( tr( "放弃文件" ), this );
	//connect( addAction, &QAction::triggered, this, &MainWindow::unDownloadPorjectAtFile );
	//fileToolBar->addAction( addAction );
	//fileMenu->addAction( addAction );
	//actionVector.emplace_back( addAction );

	//addAction = new QAction( tr( "编译->项目" ), this );
	//connect( addAction, &QAction::triggered, this, &MainWindow::builderProject );
	//builderNodeVectorBtn = addAction;
	//projectToolBar->addAction( addAction );
	//projectMenu->addAction( addAction );
	//actionVector.emplace_back( addAction );

	//addAction = new QAction( tr( "下一步->项目" ), this );
	//connect( addAction, &QAction::triggered, this, &MainWindow::runNextProject );
	//runBuilderNextNodeVectorBtn = addAction;
	//runBuilderNextNodeVectorBtn->setEnabled( false );
	//projectToolBar->addAction( addAction );
	//projectMenu->addAction( addAction );
	//actionVector.emplace_back( addAction );

	//addAction = new QAction( tr( "停止->项目" ), this );
	//connect( addAction, &QAction::triggered, this, &MainWindow::stopProject );
	//runBuilderStopNodeVectorBtn = addAction;
	//runBuilderStopNodeVectorBtn->setEnabled( false );
	//projectToolBar->addAction( addAction );
	//projectMenu->addAction( addAction );
	//actionVector.emplace_back( addAction );

	//addAction = new QAction( tr( "运行->项目" ), this );
	//connect( addAction, &QAction::triggered, this, &MainWindow::runAllProject );
	//runBuilderAllNodeVectorBtn = addAction;
	//runBuilderAllNodeVectorBtn->setEnabled( false );
	//projectToolBar->addAction( addAction );
	//projectMenu->addAction( addAction );
	//actionVector.emplace_back( addAction );

	//addAction = new QAction( tr( "清理->项目" ), this );
	//connect( addAction, &QAction::triggered, this, &MainWindow::clearProject );
	//clearBuilderNodeVectorBtn = addAction;
	//projectToolBar->addAction( addAction );
	//projectMenu->addAction( addAction );
	//actionVector.emplace_back( addAction );

	//QShortcut *shortcut;
	//shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_S ), this );
	//connect( shortcut, &QShortcut::activated, this, &MainWindow::savePorjectToFile );
	//shortcutVector.emplace_back( shortcut );

	//shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_O ), this );
	//connect( shortcut, &QShortcut::activated, this, &MainWindow::savePorjectToFile );
	//shortcutVector.emplace_back( shortcut );

	//shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_C ), this );
	//connect( shortcut, &QShortcut::activated, this, &MainWindow::copyNodeInfo );
	//shortcutVector.emplace_back( shortcut );

	//shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_V ), this );
	//connect( shortcut, &QShortcut::activated, this, &MainWindow::pasteNodeInfo );
	//shortcutVector.emplace_back( shortcut );

	//shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_X ), this );
	//connect( shortcut, &QShortcut::activated, this, &MainWindow::cutNodeInfo );
	//shortcutVector.emplace_back( shortcut );

	//shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_Z ), this );
	//connect( shortcut, &QShortcut::activated, this, &MainWindow::cancelNodeInfo );
	//shortcutVector.emplace_back( shortcut );

	//shortcut = new QShortcut( QKeySequence( Qt::Key_Delete ), this );
	//connect( shortcut, &QShortcut::activated, this, &MainWindow::deleteNodeInfo );
	//shortcutVector.emplace_back( shortcut );

	//shortcut = new QShortcut( QKeySequence( Qt::Key_Backspace ), this );
	//connect( shortcut, &QShortcut::activated, this, &MainWindow::deleteNodeInfo );
	//shortcutVector.emplace_back( shortcut );

	return true;
}
MainWindow::~MainWindow( ) {
	emit release_signal( this );
	delete mainWidget;
	delete mainWidgetScrollArea;
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
