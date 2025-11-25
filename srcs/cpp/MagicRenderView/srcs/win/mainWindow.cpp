#include "mainWindow.h"

#include <QMenu>
#include <QMouseEvent>

#include "../app/application.h"

#include "../director/nodeDirector.h"

#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"

MainWindow::MainWindow( ) : mainWidgetScrollArea( nullptr ) {
}
bool MainWindow::init( ) {
	if( mainWidgetScrollArea )
		delete mainWidgetScrollArea;
	mainWidgetScrollArea = new MainWidgetScrollArea( this );
	setCentralWidget( mainWidgetScrollArea );
	mainWidget = mainWidgetScrollArea->getMainWidget( );
	if( mainWidget->init( ) == false )
		return false;
	show( );
	if( isHidden( ) )
		return false;
	instancePtr = Application::getInstancePtr( );
	nodeDirector = instancePtr->getNodeDirector( );
	nodeCreateMenu = nodeDirector->getNodeCreateMenu( );
	return true;
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
	QMainWindow::mouseReleaseEvent( event );
	nodeCreateMenu->popup( mapToGlobal( event->pos( ) ) );
}
void MainWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
	
}
bool MainWindow::event( QEvent *event ) {
	return QMainWindow::event( event );
}
