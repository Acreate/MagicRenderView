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
#include "../menu/app/action/normalApplicationAction.h"
#include "../menu/app/imp/menu/appApplicationMenu.h"
#include "../menu/app/imp/menu/builderApplicationMenu.h"
#include "../menu/app/imp/menu/editorApplicationMenu.h"
#include "../menu/app/imp/menu/projectApplicationMenu.h"
#include "../menu/app/imp/toolBar/builderApplicationToolBar.h"
#include "../menu/app/imp/toolBar/projectApplicationToolBar.h"
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

	projectToolBar = nullptr;
	builderToolBar = nullptr;
	projectMenu = nullptr;
	builderMenu = nullptr;
	appMenu = nullptr;
	editorMenu = nullptr;
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
	if( projectToolBar )
		delete projectToolBar;
	projectToolBar = applicationMenuStack->getToolBar< ProjectApplicationToolBar >( );
	if( projectToolBar == nullptr )
		return false;

	if( builderToolBar )
		delete builderToolBar;
	builderToolBar = applicationMenuStack->getToolBar< BuilderApplicationToolBar >( );
	if( builderToolBar == nullptr )
		return false;

	if( appMenu )
		delete appMenu;
	appMenu = applicationMenuStack->getMenu< AppApplicationMenu >( );
	if( appMenu == nullptr )
		return false;

	if( projectMenu )
		delete projectMenu;
	projectMenu = applicationMenuStack->getMenu< ProjectApplicationMenu >( );
	if( projectMenu == nullptr )
		return false;

	if( editorMenu )
		delete editorMenu;
	editorMenu = applicationMenuStack->getMenu< EditorApplicationMenu >( );
	if( editorMenu == nullptr )
		return false;

	if( builderMenu )
		delete builderMenu;
	builderMenu = applicationMenuStack->getMenu< BuilderApplicationMenu >( );
	if( builderMenu == nullptr )
		return false;

	projectToolBar->setParent( this );
	addToolBar( Qt::TopToolBarArea, projectToolBar );
	projectToolBar->setFloatable( false );
	projectToolBar->setAllowedAreas( Qt::TopToolBarArea );
	projectToolBar->setMovable( true );
	connect( projectToolBar, &NormalApplicationToolBar::trigg_action_signal, this, &MainWindow::triggToolbarActionSignal );

	builderToolBar->setParent( this );
	addToolBar( Qt::TopToolBarArea, builderToolBar );
	builderToolBar->setFloatable( false );
	builderToolBar->setAllowedAreas( Qt::TopToolBarArea );
	builderToolBar->setMovable( true );
	connect( builderToolBar, &NormalApplicationToolBar::trigg_action_signal, this, &MainWindow::triggToolbarActionSignal );

	appMenuBar->addMenu( appMenu );
	connect( appMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );
	appMenuBar->addMenu( projectMenu );
	connect( projectMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );
	appMenuBar->addMenu( editorMenu );
	connect( editorMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );
	appMenuBar->addMenu( builderMenu );
	connect( builderMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );

	return true;
}
void MainWindow::triggActionSignal( NormalApplicationAction *action ) {
	if( action->run( this ) == false )
		printerDirector->info( tr( "NormalApplicationAction [%1] 执行异常" ).arg( action->text( ) ),Create_SrackInfo( ) );
}
void MainWindow::triggMenuActionSignal( NormalApplicationMenu *normal_application_menu, NormalApplicationAction *action ) {
	if( action->run( this ) == false )
		printerDirector->info( tr( "NormalApplicationMenu [%1] , NormalApplicationAction [%2] 执行异常" ).arg( normal_application_menu->title( ) ).arg( action->text( ) ),Create_SrackInfo( ) );
}
void MainWindow::triggToolbarActionSignal( NormalApplicationToolBar *normal_application_tool_bar, NormalApplicationAction *action ) {
	if( action->run( this ) == false )
		printerDirector->info( tr( "NormalApplicationToolBar [%1] , NormalApplicationAction [%2] 执行异常" ).arg( normal_application_tool_bar->windowTitle( ) ).arg( action->text( ) ),Create_SrackInfo( ) );
}
MainWindow::~MainWindow( ) {
	emit release_signal( this );
	if( projectMenu )
		delete projectMenu;
	if( builderMenu )
		delete builderMenu;
	if( appMenu )
		delete appMenu;
	if( editorMenu )
		delete editorMenu;
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
