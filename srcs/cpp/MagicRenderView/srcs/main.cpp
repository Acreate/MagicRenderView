#include "qt/application/application.h"
#include "qt/mainWindows/mainWindow.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );

	return app.exec( );
}