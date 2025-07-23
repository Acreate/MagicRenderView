#include "mainWindow.h"

#include <qguiapplication.h>
#include <QMenuBar>
#include <QProcess>
#include <QFileDialog>
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

	mainWidget = new MainWidget( );
	setCentralWidget( mainWidget );
	setWindowToIndexScreenCentre( 0 );
}
void MainWindow::setWindowToIndexScreenCentre( size_t index ) {
	tools::ui::moveDisplayCenter( this, index );
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
}
void MainWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
}
