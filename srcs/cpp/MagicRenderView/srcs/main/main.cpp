#include <app/applicationInstance/application.h>

#include <win/mainWindow/mainWindow.h>

int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false )
		return -1;

	MainWindow mainwidget;
	mainwidget.show( );

	int exec = app.exec( );
	return exec;
}
