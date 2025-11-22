#include "mainWindow.h"

#include "../../app/applicationInstance/application.h"
#include "../../app/printfInfo/printfInfo.h"

#include "../../widget/mainWidget/mainWidget.h"
#include "../../widget/scrollArea/mainWidgetScrollArea.h"
MainWindow::MainWindow( ) {
	mainWidgetScrollArea = new MainWidgetScrollArea( this );
	setCentralWidget( mainWidgetScrollArea );
	mainWidget = mainWidgetScrollArea->getMainWidget( );
}
