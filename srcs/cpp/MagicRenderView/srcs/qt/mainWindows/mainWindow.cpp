#include "mainWindow.h"

#include <qguiapplication.h>
#include <QMenuBar>
#include <QProcess>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPushButton>

#include <qt/tools/tools.h>

#include "../application/application.h"

#include "../widgets/widgets/mainWidget.h"

MainWindow::MainWindow( QWidget *parent, Qt::WindowFlags flags ): QMainWindow( parent, flags ) {

	mainMenuBar = menuBar( );
	if( mainMenuBar == nullptr )
		mainMenuBar = new QMenuBar( this );

	mainMenu = new QMenu( "应用", this );
	mainMenuBar->addMenu( mainMenu );

	QAction *action;
	action = mainMenu->addAction( "重启" );
	connect( action, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->resetApp( );
	} );
	action = mainMenu->addAction( "退出" );
	connect( action, &QAction::triggered, [this]( ) {
		Application::getApplicationInstancePtr( )->quitApp( );
	} );

	setWindowToIndexScreenCentre( 0 );

	appInstance = Application::getApplicationInstancePtr( );
	keyFirst = "Application/MainWindow";

	QSize size = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "size" ), this->contentsRect( ).size( ) ).toSize( );
	setBaseSize( size );

	QPoint point = appInstance->getAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "pos" ), this->pos( ) ).toPoint( );
	move( point );

	mainWidget = new MainWidget( this );
	setCentralWidget( mainWidget );
	
	
	setMouseTracking( true );
	mainWidget->setMouseTracking( true );
}
MainWindow::~MainWindow( ) {
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "size" ), this->contentsRect( ).size( ) );
	appInstance->setAppIniValue( appInstance->normalKeyAppendEnd( keyFirst, this, "pos" ), this->pos( ) );
	appInstance->syncAppValueIniFile( );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
}
