#include "menuDirector.h"

#include <QFileDialog>
#include <QShortcut>
#include <QAction>

#include "../app/application.h"
#include "../menu/createNodeMenu.h"
#include "../menu/editorNodeMenu.h"
#include "../menu/freeMenu.h"
#include "../menu/windowMenu.h"
#include "../node/nodeInfo/nodeRunInfo.h"
#include "../srack/srackInfo.h"
#include "../tools/path.h"
#include "nodeDirector.h"
#include "printerDirector.h"
MenuDirector::MenuDirector( QObject *parent ) : QObject( parent ) {
	saveFileDirPath.clear( );
	instancePtr = nullptr;
	nodeDirector = nullptr;
	printerDirector = nullptr;
	mainWindow = nullptr;
	mainWidget = nullptr;
	builderNodeVectorBtn = nullptr;
	runBuilderAllNodeVectorBtn = nullptr;
	runBuilderNextNodeVectorBtn = nullptr;
	runBuilderStopNodeVectorBtn = nullptr;
	clearBuilderNodeVectorBtn = nullptr;
	nodeRunBuilderObj = nullptr;

	createNodeMenu = new CreateNodeMenu;
	editorNodeMenu = new EditorNodeMenu;
	freeMenu = new FreeMenu;
	windowMenu = new WindowMenu;
}

MenuDirector::~MenuDirector( ) {
	emit release_signal( this, Create_SrackInfo( ) );
	delete createNodeMenu;
	delete editorNodeMenu;
	delete freeMenu;
	delete windowMenu;
}
bool MenuDirector::init( ) {
	if( createNodeMenu->initCreateNodeMenu( ) == false )
		return false;
	if( editorNodeMenu->initEditorNodeMenu( ) == false )
		return false;
	if( freeMenu->initFreeMenu( ) == false )
		return false;
	if( windowMenu->initWindowMenu( ) == false )
		return false;
	// 释放节点
	if( nodeDirector ) {
		disconnect( nodeDirector, &NodeDirector::node_run_info_clear_signal, this, &MenuDirector::node_run_info_clear_slot );
	}
	instancePtr = Application::getInstancePtr( );
	nodeDirector = instancePtr->getNodeDirector( );

	connect( nodeDirector, &NodeDirector::node_run_info_clear_signal, this, &MenuDirector::node_run_info_clear_slot );

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

	if( nodeRunBuilderObj ) {
		nodeRunBuilderObj->clear( );
		nodeRunBuilderObj = nullptr;
	}

	printerDirector = instancePtr->getPrinterDirector( );

	auto addAction = new QAction( tr( "保存文件..." ), this );
	connect( addAction, &QAction::triggered, this, &MenuDirector::savePorjectToFile );
	actionVector.emplace_back( addAction );
	addAction = new QAction( tr( "加载文件..." ), this );
	connect( addAction, &QAction::triggered, this, &MenuDirector::loadPorjectAtFile );
	actionVector.emplace_back( addAction );
	addAction = new QAction( tr( "放弃文件" ), this );
	connect( addAction, &QAction::triggered, this, &MenuDirector::unDownloadPorjectAtFile );
	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "编译->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MenuDirector::builderProject );
	builderNodeVectorBtn = addAction;
	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "下一步->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MenuDirector::runNextProject );
	runBuilderNextNodeVectorBtn = addAction;
	runBuilderNextNodeVectorBtn->setEnabled( false );

	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "停止->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MenuDirector::stopProject );
	runBuilderStopNodeVectorBtn = addAction;
	runBuilderStopNodeVectorBtn->setEnabled( false );

	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "运行->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MenuDirector::runAllProject );
	runBuilderAllNodeVectorBtn = addAction;
	runBuilderAllNodeVectorBtn->setEnabled( false );

	actionVector.emplace_back( addAction );

	addAction = new QAction( tr( "清理->项目" ), this );
	connect( addAction, &QAction::triggered, this, &MenuDirector::clearProject );
	clearBuilderNodeVectorBtn = addAction;

	actionVector.emplace_back( addAction );

	QShortcut *shortcut;
	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_S ), this );
	connect( shortcut, &QShortcut::activated, this, &MenuDirector::savePorjectToFile );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_O ), this );
	connect( shortcut, &QShortcut::activated, this, &MenuDirector::savePorjectToFile );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_C ), this );
	connect( shortcut, &QShortcut::activated, this, &MenuDirector::copyNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_V ), this );
	connect( shortcut, &QShortcut::activated, this, &MenuDirector::pasteNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_X ), this );
	connect( shortcut, &QShortcut::activated, this, &MenuDirector::cutNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::CTRL + Qt::Key_Z ), this );
	connect( shortcut, &QShortcut::activated, this, &MenuDirector::cancelNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::Key_Delete ), this );
	connect( shortcut, &QShortcut::activated, this, &MenuDirector::deleteNodeInfo );
	shortcutVector.emplace_back( shortcut );

	shortcut = new QShortcut( QKeySequence( Qt::Key_Backspace ), this );
	connect( shortcut, &QShortcut::activated, this, &MenuDirector::deleteNodeInfo );
	shortcutVector.emplace_back( shortcut );

	return true;
}

void MenuDirector::savePorjectToFile( ) {
	auto openFileName = QFileDialog::getSaveFileName( nullptr, tr( "保存文件" ), saveFileDirPath, tr( "魔术窗口 (*.mrv)" ) );
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
void MenuDirector::loadPorjectAtFile( ) {
	auto openFileName = QFileDialog::getOpenFileName( nullptr, tr( "保存文件" ), saveFileDirPath, tr( "魔术窗口 (*.mrv)" ) );
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

void MenuDirector::node_run_info_clear_slot( NodeDirector *signal_obj_ptr, const SrackInfo &srack_info, NodeRunInfo *clear_obj, const SrackInfo &org_srack_info ) {
	if( clear_obj != nodeRunBuilderObj )
		return;
	nodeRunBuilderObj = nullptr;
	runBuilderAllNodeVectorBtn->setEnabled( false );
	runBuilderNextNodeVectorBtn->setEnabled( false );
	runBuilderStopNodeVectorBtn->setEnabled( false );
}

void MenuDirector::unDownloadPorjectAtFile( ) {
	nodeDirector->init( );
}
void MenuDirector::copyNodeInfo( ) {
	mainWidget->copySelectNodeInfo( );
}
void MenuDirector::pasteNodeInfo( ) {
	mainWidget->pastePointNodeInfo( );
}
void MenuDirector::cutNodeInfo( ) {
	mainWidget->cutSelectNodeInfo( );
}
void MenuDirector::cancelNodeInfo( ) {
	mainWidget->cancelNodeInfo( );
}
void MenuDirector::deleteNodeInfo( ) {
	mainWidget->deleteSelectNodeInfo( );
}
void MenuDirector::builderProject( ) {
	if( nodeRunBuilderObj )
		nodeRunBuilderObj->clear( );
	nodeRunBuilderObj = nullptr;
	nodeRunBuilderObj = nodeDirector->builderCurrentAllNode( this->mainWidget );
	if( nodeRunBuilderObj == nullptr )
		return;
	runBuilderAllNodeVectorBtn->setEnabled( true );
	runBuilderNextNodeVectorBtn->setEnabled( true );
	runBuilderStopNodeVectorBtn->setEnabled( true );
}
void MenuDirector::runAllProject( ) {
}
void MenuDirector::runNextProject( ) {
}
void MenuDirector::stopProject( ) {

}
void MenuDirector::clearProject( ) {
	if( nodeRunBuilderObj == nullptr )
		return;
	nodeRunBuilderObj->clear( );
	nodeRunBuilderObj = nullptr;
}
