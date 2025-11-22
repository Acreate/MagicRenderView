#include "mainWindow.h"

#include "../widget/mainWidgetScrollArea.h"

MainWindow::MainWindow( ) {
	mainWidgetScrollArea = new MainWidgetScrollArea( this );
	setCentralWidget( mainWidgetScrollArea );
	mainWidget = mainWidgetScrollArea->getMainWidget( );
}
