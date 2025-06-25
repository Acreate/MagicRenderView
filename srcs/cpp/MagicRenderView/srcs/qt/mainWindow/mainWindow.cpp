#include "mainWindow.h"

#include <qguiapplication.h>
#include <QMenuBar>
#include <QFileDialog>
#include <QPushButton>

#include <qt/tools/tools.h>

#include <qt/widget/scrollArea/scrollNodeGraph.h>
#include <qt/widget/scrollArea/scrollNodeInfo.h>
#include <qt/widget/scrollArea/scrollNodeList.h>
#include <qt/widget/nodeGraph.h>
#include <qt/widget/nodeInfo.h>
#include <qt/widget/nodeList.h>

#include "../stack/varStack/base/baseVarStackEx.h"

#include "../type/baseType/dataTypeObject.h"
#include "../type/baseType/floatTypeObject.h"
#include "../type/baseType/intTypeObject.h"

#include "../widget/infoWidget/infoBaseWidget/combinationWidget.h"
#include "../widget/infoWidget/infoBaseWidget/dataWidget.h"
#include "../widget/infoWidget/infoBaseWidget/vectorWidget.h"
MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ): QMainWindow( parent, flags ) {
	auto varStack = IVarStack::getInstance< BaseVarStackEx >( );
	std_shared_ptr< ITypeObject > generateTubVar;
	IInfoWidget *central;

	CombinationWidget *vectorWidget = new CombinationWidget( nullptr, this, "结构体" );
	generateTubVar = varStack->generateTVar< IntTypeObject >( );
	generateTubVar->setUiTypeName( "整数" );
	vectorWidget->append( generateTubVar->getUiTypeNames( )[ 0 ], generateTubVar );
	generateTubVar = varStack->generateTVar< FloatTypeObject >( );
	generateTubVar->setUiTypeName( "浮点" );
	vectorWidget->append( generateTubVar->getUiTypeNames( )[ 0 ], generateTubVar );
	qDebug( ) << __LINE__ << " : " << vectorWidget->getValue( )->toString( );

	central = vectorWidget;
	if( central )
		setCentralWidget( central );
	setWindowToIndexScreenCentre( 0 );
	return;

	nodeGraph = new ScrollNodeGraph( this );
	NodeGraph *graph = nodeGraph->getNodeGraph( );
	graph->setMainWindow( this );
	setCentralWidget( nodeGraph );
	nodeGraph->show( );

	nodeInfo = new ScrollNodeInfo( this );
	nodeInfo->getNodeInfo( )->setMainWindow( this );

	connect( graph, &NodeGraph::selectActiveNodeWidget, [this] ( NodeGraph *node_graph, INodeWidget *now_select_active_node_widget, INodeWidget *old_select_active_node_widget ) {
		if( now_select_active_node_widget == nullptr )
			return;
		NodeInfo *info = nodeInfo->getNodeInfo( );
		info->setNodeWidget( now_select_active_node_widget );
	} );

	nodeList = new ScrollNodeList( this );
	nodeList->getNodeList( )->setMainWindow( this );

	connect( graph, &NodeGraph::generateNodeWidget, [this] ( NodeGraph *node_graph, INodeWidget *new_active_node_widget, const std_vector< INodeWidget * > &node_widgets ) {
		if( new_active_node_widget == nullptr )
			return;
		nodeList->getNodeList( )->setCurrentNodeWidgets( node_widgets );
	} );

	listBtn = new QPushButton( this );
	listBtn->setText( "节点列表" );
	connect( listBtn, &QPushButton::clicked, [this] ( bool flag ) {
		if( nodeList->isHidden( ) )
			nodeList->show( );
		else
			nodeList->hide( );
	} );

	infoBtn = new QPushButton( this );
	infoBtn->setText( "节点信息" );
	connect( infoBtn, &QPushButton::clicked, [this] ( bool flag ) {
		if( nodeInfo->isHidden( ) )
			nodeInfo->show( );
		else
			nodeInfo->hide( );
	} );

	auto thisSize = size( );
	listBtn->move( 10, listBtn->height( ) );
	infoBtn->move( thisSize.width( ) - listBtn->width( ) - 20, infoBtn->height( ) );

	auto geometry = listBtn->geometry( );
	nodeList->setGeometry( geometry.x( ), geometry.y( ) + geometry.height( ), geometry.width( ) + 10, thisSize.height( ) - geometry.height( ) - geometry.y( ) - 20 );
	geometry = infoBtn->geometry( );
	nodeInfo->setGeometry( geometry.x( ) - 10, geometry.y( ) + geometry.height( ), geometry.width( ) + 10, thisSize.height( ) - geometry.height( ) - geometry.y( ) - 20 );

	auto minWidth = nodeList->width( ) + nodeInfo->width( ) + 10 * 4;
	setMinimumSize( minWidth, 264 );

	setWindowToIndexScreenCentre( 0 );
	mainMenuBar = menuBar( );
	if( mainMenuBar == nullptr )
		mainMenuBar = new QMenuBar( this );
	setMenuBar( mainMenuBar );
	QMenu *firstMenu = new QMenu( this );
	firstMenu->setTitle( "首要" );
	mainMenuBar->addMenu( firstMenu );
	auto openFileAction = firstMenu->addAction( "打开文件..." );

	connect( openFileAction, &QAction::triggered, [this]( ) {
		QString openFileName = QFileDialog::getOpenFileName( this, "打开文件", qApp->applicationDirPath( ), "艺术文件(*.mser)" );
		if( openFileName.isEmpty( ) )
			return;
		QFile file( openFileName );
		if( file.open( QIODeviceBase::ReadOnly ) ) {
			QByteArray byteArray = file.readAll( );
			if( nodeGraph->getNodeGraph( )->serializeToObjectData( ( const uchar * ) byteArray.data( ), byteArray.size( ) ) == 0 ) {
				tools::debug::printError( "文件无法读取，或者内容失败 : " + file.fileName( ) );
			}
			file.close( );
		}
	} );
	auto saveFileAction = firstMenu->addAction( "存储文件..." );

	connect( saveFileAction, &QAction::triggered, [this]( ) {
		QString openFileName = QFileDialog::getSaveFileName( this, "存储文件", qApp->applicationDirPath( ), "艺术文件(*.mser)" );
		if( openFileName.isEmpty( ) )
			return;
		QFile file( openFileName );
		if( file.open( QIODeviceBase::WriteOnly ) ) {
			std_vector< uchar > ser;
			if( nodeGraph->getNodeGraph( )->serializeToVectorData( &ser ) )
				file.write( ( const char * ) ser.data( ), ser.size( ) );
			file.close( );
		}
	} );
	firstMenu->addSeparator( );
	auto exitAction = firstMenu->addAction( "退出" );
	connect( exitAction, &QAction::triggered, []( ) {
		qApp->quit( );
	} );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
}
void MainWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
	return;
	auto thisSize = size( );
	listBtn->move( 10, listBtn->height( ) );
	infoBtn->move( thisSize.width( ) - listBtn->width( ) - 20, infoBtn->height( ) );

	auto minWidth = thisSize.width( ) / 3;

	auto geometry = listBtn->geometry( );
	nodeList->setGeometry( geometry.x( ), geometry.y( ) + geometry.height( ), minWidth, thisSize.height( ) - geometry.height( ) - geometry.y( ) - 20 );
	geometry = infoBtn->geometry( );
	nodeInfo->setGeometry( geometry.x( ) - minWidth + geometry.width( ), geometry.y( ) + geometry.height( ), minWidth, thisSize.height( ) - geometry.height( ) - geometry.y( ) - 20 );
}
