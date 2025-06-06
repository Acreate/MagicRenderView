#include "qt/application/application.h"
#include "qt/mainWindow/mainWindow.h"
#include "qt/tools/tools.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
