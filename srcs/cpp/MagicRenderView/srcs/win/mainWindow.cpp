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
#include "../menu/app/normalApplicationMenu.h"
#include "../menu/app/normalApplicationToolBar.h"
#include "../menuStack/app/applicationMenuStack.h"
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

	fileToolBar = nullptr;
	projectToolBar = nullptr;
	fileMenu = nullptr;
	projectMenu = nullptr;

	appMenuBar = menuBar( );
	if( appMenuBar == nullptr ) {
		appMenuBar = new QMenuBar( this );
		setMenuBar( appMenuBar );
	}

}
bool MainWindow::init( ) {
	if( mainWidget->init( ) == false )
		return false;
	instancePtr = Application::getInstancePtr( );
	nodeDirector = instancePtr->getNodeDirector( );
	printerDirector = instancePtr->getPrinterDirector( );
	saveFileDirPath = instancePtr->applicationDirPath( );
	auto applicationMenuStack = instancePtr->getApplicationMenuStack( );
	if( fileToolBar )
		delete fileToolBar;
	fileToolBar = applicationMenuStack->getToolBar( tr( "文件" ) );
	if( fileToolBar == nullptr )
		return false;
	fileToolBar->setParent( this );
	addToolBar( Qt::TopToolBarArea, fileToolBar );
	fileToolBar->setFloatable( false );
	fileToolBar->setAllowedAreas( Qt::TopToolBarArea );
	fileToolBar->setMovable( true );

	if( projectToolBar )
		delete projectToolBar;
	projectToolBar = applicationMenuStack->getToolBar( tr( "项目" ) );
	if( projectToolBar == nullptr )
		return false;
	projectToolBar->setParent( this );
	addToolBar( Qt::TopToolBarArea, projectToolBar );
	projectToolBar->setFloatable( false );
	projectToolBar->setAllowedAreas( Qt::TopToolBarArea );
	projectToolBar->setMovable( true );

	fileMenu = applicationMenuStack->getMenu( tr( "文件" ) );
	if( fileMenu )
		delete fileMenu;
	if( fileMenu == nullptr )
		return false;
	fileMenu->setParent( this );
	appMenuBar->addMenu( fileMenu );
	
	if( projectMenu )
		delete projectMenu;
	projectMenu = applicationMenuStack->getMenu( tr( "项目" ) );
	if( projectMenu == nullptr )
		return false;
	projectMenu->setParent( this );
	appMenuBar->addMenu( projectMenu );
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
