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

#include "../srack/srackInfo.h"

#include "../tools/path.h"

#include "../widget/drawLinkWidget.h"
#include "../widget/drawNodeWidget.h"
#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"

void MainWindow::release_node_slot( NodeDirector *signal_obj_ptr, Node *release_node, const SrackInfo &srack_info ) {
}
void MainWindow::finish_release_port_link_slot( NodeDirector *signal_obj_ptr, InputPort *signal_port, OutputPort *target_prot, const SrackInfo &srack_info ) {
}
void MainWindow::finish_create_port_link_slot( NodeDirector *signal_obj_ptr, InputPort *signal_port, OutputPort *target_prot, const SrackInfo &srack_info ) {
}
void MainWindow::finish_release_ref_node_slot( NodeDirector *signal_obj_ptr, Node *signal_node, Node *ref_node, const SrackInfo &srack_info ) {
}
void MainWindow::finish_create_ref_node_slot( NodeDirector *signal_obj_ptr, Node *signal_node, Node *ref_node, const SrackInfo &srack_info ) {
}
void MainWindow::error_run_node_slot( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *error_node, const SrackInfo &org_srack_info, NodeEnum::ErrorType error_type, const QString &error_msg ) {
}
void MainWindow::advise_run_node_slot( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *advise_node, const SrackInfo &org_srack_info, NodeEnum::AdviseType advise_type, const QString &advise_msg ) {
}
void MainWindow::finish_run_node_slot( NodeDirector *signal_obj_ptr, const SrackInfo &signal_srack_info, Node *finish_node, const SrackInfo &org_srack_info ) {
}
void MainWindow::finish_create_node_slot( NodeDirector *signal_obj_ptr, Node *create_node, const SrackInfo &srack_info ) {
}
void MainWindow::error_create_node_slot( NodeDirector *signal_obj_ptr, const QString &create_name, NodeEnum::CreateType error_type_info, const QString &error_msg, const SrackInfo &srack_info ) {
}
MainWindow::MainWindow( ) : mainWidgetScrollArea( nullptr ) {

	instancePtr = nullptr;
	nodeDirector = nullptr;
	printerDirector = nullptr;
	drawNodeWidget = nullptr;
	drawLinkWidget = nullptr;
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
	size_t count = shortcutVector.size( );
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
	actionVector.clear( );

	instancePtr = Application::getInstancePtr( );
	// 释放节点
	if( nodeDirector ) {
		disconnect( nodeDirector, &NodeDirector::release_node_signal, this, &MainWindow::release_node_slot );
		disconnect( nodeDirector, &NodeDirector::finish_release_port_link_signal, this, &MainWindow::finish_release_port_link_slot );
		disconnect( nodeDirector, &NodeDirector::finish_create_port_link_signal, this, &MainWindow::finish_create_port_link_slot );
		disconnect( nodeDirector, &NodeDirector::finish_release_ref_node_signal, this, &MainWindow::finish_release_ref_node_slot );
		disconnect( nodeDirector, &NodeDirector::finish_create_ref_node_signal, this, &MainWindow::finish_create_ref_node_slot );
		disconnect( nodeDirector, &NodeDirector::error_run_node_signal, this, &MainWindow::error_run_node_slot );
		disconnect( nodeDirector, &NodeDirector::advise_run_node_signal, this, &MainWindow::advise_run_node_slot );
		disconnect( nodeDirector, &NodeDirector::finish_run_node_signal, this, &MainWindow::finish_run_node_slot );
		disconnect( nodeDirector, &NodeDirector::finish_create_node_signal, this, &MainWindow::finish_create_node_slot );
		disconnect( nodeDirector, &NodeDirector::error_create_node_signal, this, &MainWindow::error_create_node_slot );
	}
	nodeDirector = instancePtr->getNodeDirector( );
	connect( nodeDirector, &NodeDirector::release_node_signal, this, &MainWindow::release_node_slot );
	connect( nodeDirector, &NodeDirector::finish_release_port_link_signal, this, &MainWindow::finish_release_port_link_slot );
	connect( nodeDirector, &NodeDirector::finish_create_port_link_signal, this, &MainWindow::finish_create_port_link_slot );
	connect( nodeDirector, &NodeDirector::finish_release_ref_node_signal, this, &MainWindow::finish_release_ref_node_slot );
	connect( nodeDirector, &NodeDirector::finish_create_ref_node_signal, this, &MainWindow::finish_create_ref_node_slot );
	connect( nodeDirector, &NodeDirector::error_run_node_signal, this, &MainWindow::error_run_node_slot );
	connect( nodeDirector, &NodeDirector::advise_run_node_signal, this, &MainWindow::advise_run_node_slot );
	connect( nodeDirector, &NodeDirector::finish_run_node_signal, this, &MainWindow::finish_run_node_slot );
	connect( nodeDirector, &NodeDirector::finish_create_node_signal, this, &MainWindow::finish_create_node_slot );
	connect( nodeDirector, &NodeDirector::error_create_node_signal, this, &MainWindow::error_create_node_slot );

	printerDirector = instancePtr->getPrinterDirector( );
	drawNodeWidget = mainWidget->getDrawNodeWidget( );
	drawLinkWidget = mainWidget->getDrawLinkWidget( );
	saveFileDirPath = instancePtr->applicationDirPath( );
	fileToolBar->clear( );
	projectToolBar->clear( );

	auto addAction = new QAction( tr( "保存文件..." ), this );
	connect( addAction, &QAction::triggered, this, &MainWindow::savePorjectToFile );
	fileToolBar->addAction( addAction );
	fileMenu->addAction( addAction );
	actionVector.emplace_back( addAction );
	addAction = new QAction( tr( "加载文件..." ), this );
	connect( addAction, &QAction::triggered, this, &MainWindow::loadPorjectAtFile );
	fileToolBar->addAction( addAction );
	fileMenu->addAction( addAction );
	actionVector.emplace_back( addAction );
	addAction = new QAction( tr( "放弃文件" ), this );
	connect( addAction, &QAction::triggered, this, &MainWindow::unDownloadPorjectAtFile );
	fileToolBar->addAction( addAction );
	fileMenu->addAction( addAction );
	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "编译->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MainWindow::builderProject );
	builderNodeVectorBtn = addAction;
	projectToolBar->addAction( addAction );
	projectMenu->addAction( addAction );
	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "下一步->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MainWindow::runNextProject );
	runBuilderNextNodeVectorBtn = addAction;
	runBuilderNextNodeVectorBtn->setEnabled( false );
	projectToolBar->addAction( addAction );
	projectMenu->addAction( addAction );
	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "停止->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MainWindow::stopProject );
	runBuilderStopNodeVectorBtn = addAction;
	runBuilderStopNodeVectorBtn->setEnabled( false );
	projectToolBar->addAction( addAction );
	projectMenu->addAction( addAction );
	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "运行->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MainWindow::runAllProject );
	runBuilderAllNodeVectorBtn = addAction;
	runBuilderAllNodeVectorBtn->setEnabled( false );
	projectToolBar->addAction( addAction );
	projectMenu->addAction( addAction );
	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "清理->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MainWindow::clearProject );
	clearBuilderNodeVectorBtn = addAction;
	projectToolBar->addAction( addAction );
	projectMenu->addAction( addAction );
	actionVector.emplace_back( addAction );

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
	delete mainWidget;
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
void MainWindow::builderProject( ) {
}
void MainWindow::runAllProject( ) {
}
void MainWindow::runNextProject( ) {
}
void MainWindow::stopProject( ) {
}
void MainWindow::clearProject( ) {
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
