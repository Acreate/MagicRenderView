#include "mainWindow.h"

#include <QMenu>
#include <QMouseEvent>

#include "../app/application.h"

#include "../director/nodeDirector.h"

#include "../widget/drawLinkWidget.h"
#include "../widget/drawNodeWidget.h"
#include "../widget/mainWidget.h"
#include "../widget/mainWidgetScrollArea.h"

MainWindow::MainWindow( ) : mainWidgetScrollArea( nullptr ) {
	mainWidgetScrollArea = new MainWidgetScrollArea( this );
	setCentralWidget( mainWidgetScrollArea );
	mainWidget = mainWidgetScrollArea->getMainWidget( );
	hide( );
}
bool MainWindow::init( ) {
	if( mainWidget->init( ) == false )
		return false;
	instancePtr = Application::getInstancePtr( );
	nodeDirector = instancePtr->getNodeDirector( );
	drawNodeWidget = mainWidget->getDrawNodeWidget( );
	drawLinkWidget = mainWidget->getDrawLinkWidget( );
	return true;
}
MainWindow::~MainWindow( ) {
	emit release_signal( this );
	delete mainWidgetScrollArea;
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
	QMainWindow::mouseReleaseEvent( event );

}
void MainWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );

}
bool MainWindow::event( QEvent *event ) {
	return QMainWindow::event( event );
}
