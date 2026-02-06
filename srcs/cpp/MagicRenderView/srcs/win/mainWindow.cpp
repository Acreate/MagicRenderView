#include "mainWindow.h"

#include <QShortcut>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenuBar>
#include <QMouseEvent>
#include <QScrollBar>

#include "../app/application.h"

#include "../director/nodeDirector.h"
#include "../director/printerDirector.h"
#include "../menu/app/action/normalApplicationAction.h"
#include "../menu/app/imp/action/builder/runToTargetNodeBuilderAction.h"
#include "../menu/app/imp/menu/builderApplicationMenu.h"
#include "../menu/app/imp/menu/editorApplicationMenu.h"
#include "../menu/app/imp/menu/fileApplicationMenu.h"
#include "../menu/app/imp/menu/helpApplicationMenu.h"
#include "../menu/app/imp/menu/projectApplicationMenu.h"
#include "../menu/app/imp/toolBar/builderApplicationToolBar.h"
#include "../menu/app/normalApplicationMenu.h"
#include "../menu/app/normalApplicationToolBar.h"
#include "../menuStack/app/applicationMenuStack.h"

#include "../srack/srackInfo.h"

#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"
#include "aboutApplicationWindow.h"

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

	builderToolBar = nullptr;
	projectMenu = nullptr;
	builderMenu = nullptr;
	fileMenu = nullptr;
	helpMenu = nullptr;
	editorMenu = nullptr;
	appMenuBar = menuBar( );
	if( appMenuBar == nullptr ) {
		appMenuBar = new QMenuBar( this );
		setMenuBar( appMenuBar );
	}
	aboutApplicationWindowPtr = new AboutApplicationWindow( this );
}
bool MainWindow::init( ) {
	if( mainWidget->init( ) == false )
		return false;
	instancePtr = Application::getInstancePtr( );
	nodeDirector = instancePtr->getNodeDirector( );
	printerDirector = instancePtr->getPrinterDirector( );
	saveFileDirPath = instancePtr->applicationDirPath( );
	auto applicationMenuStack = instancePtr->getApplicationMenuStack( );

	if( builderToolBar )
		delete builderToolBar;
	builderToolBar = applicationMenuStack->getToolBar< BuilderApplicationToolBar >( );
	if( builderToolBar == nullptr )
		return false;

	if( fileMenu )
		delete fileMenu;
	fileMenu = applicationMenuStack->getMenu< FileApplicationMenu >( );
	if( fileMenu == nullptr )
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

	if( helpMenu )
		delete helpMenu;
	helpMenu = applicationMenuStack->getMenu< HelpApplicationMenu >( );
	if( helpMenu == nullptr )
		return false;

	if( builderMenu )
		delete builderMenu;
	builderMenu = applicationMenuStack->getMenu< BuilderApplicationMenu >( );
	if( builderMenu == nullptr )
		return false;

	builderToolBar->setParent( this );
	addToolBar( Qt::TopToolBarArea, builderToolBar );
	builderToolBar->setFloatable( false );
	builderToolBar->setAllowedAreas( Qt::TopToolBarArea );
	builderToolBar->setMovable( true );
	connect( builderToolBar, &NormalApplicationToolBar::trigg_action_signal, this, &MainWindow::triggToolbarActionSignal );

	appMenuBar->addMenu( fileMenu );
	connect( fileMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );
	appMenuBar->addMenu( projectMenu );
	connect( projectMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );
	appMenuBar->addMenu( editorMenu );
	connect( editorMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );
	appMenuBar->addMenu( builderMenu );
	connect( builderMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );
	appMenuBar->addMenu( helpMenu );
	connect( helpMenu, &NormalApplicationMenu::trigg_action_signal, this, &MainWindow::triggMenuActionSignal );

	connect( mainWidget, &MainWidget::select_node_signal, this, &MainWindow::selectNode_Slot );
	return true;
}
void MainWindow::selectNode_Slot( MainWidget *sender_signal_ptr, Node *select_node_ptr ) {
	builderMenu->getNormalMenuAction( ).runToTargetNodeBuilderAction->setTargetNode( select_node_ptr );
	builderToolBar->getNormalToolBarAction( ).runToTargetNodeBuilderAction->setTargetNode( select_node_ptr );
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
void MainWindow::select_node_Signal( MainWidget *sender_signal_ptr, Node *select_node_ptr ) {
	if( builderMenu == nullptr )
		return;
	auto &menuAction = builderMenu->getNormalMenuAction( );
	if( menuAction.runToTargetNodeBuilderAction->isEnabled( ) == false )
		return;
	selectNode_Slot( mainWidget, select_node_ptr );
}
MainWindow::~MainWindow( ) {
	emit release_signal( this );
	if( projectMenu )
		delete projectMenu;
	if( builderMenu )
		delete builderMenu;
	if( fileMenu )
		delete fileMenu;
	if( editorMenu )
		delete editorMenu;
	if( helpMenu )
		delete helpMenu;
	delete aboutApplicationWindowPtr;
	delete mainWidget;
	delete mainWidgetScrollArea;
}
bool MainWindow::popAboutApplicationWindow( ) {
	aboutApplicationWindowPtr->show( );
	return aboutApplicationWindowPtr;
}
bool MainWindow::copySelectNodeInfo( ) {
	if( mainWidget == nullptr )
		return false;
	return mainWidget->copySelectNodeInfo( );
}
bool MainWindow::pastePointNodeInfo( ) {
	if( mainWidget == nullptr )
		return false;
	return mainWidget->pastePointNodeInfo( );
}
bool MainWindow::cutSelectNodeInfo( ) {
	if( mainWidget == nullptr )
		return false;
	return mainWidget->cutSelectNodeInfo( );
}
bool MainWindow::cancelNodeInfo( ) {
	if( mainWidget == nullptr )
		return false;
	return mainWidget->cancelNodeInfo( );
}
bool MainWindow::deleteSelectNodeInfo( ) {
	if( mainWidget == nullptr )
		return false;
	return mainWidget->deleteSelectNodeInfo( );
}
bool MainWindow::calculateNodeRenderSize( ) {
	if( mainWidget == nullptr )
		return false;
	return mainWidget->calculateNodeRenderSize( );
}
bool MainWindow::runToNode( Node *target_node ) {
	auto &menuAction = builderMenu->getNormalMenuAction( );
	selectNode_Slot( mainWidget, target_node );
	if( menuAction.runToTargetNodeBuilderAction->isEnabled( ) == false )
		return false;
	menuAction.runToTargetNodeBuilderAction->activate( QAction::Trigger );
	return false;
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
void MainWindow::closeEvent( QCloseEvent *event ) {
	QMainWindow::closeEvent( event );
	instancePtr->quit( );
}
