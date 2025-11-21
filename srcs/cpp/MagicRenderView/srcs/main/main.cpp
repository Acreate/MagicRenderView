#include "../app/applicationInstance/application.h"
#include "../app/printfInfo/printfInfo.h"

#include "../win/mainWindow/mainWindow.h"

void pr( ) {
	Application::getInstancePtr( )->getPrintfInfo( )->info( "提示" );
}

void prs( ) {
	pr( );
}
int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	Application::setInstancePtr( &app );
	prs( );
	MainWindow mainwidget;
	mainwidget.show( );

	return app.exec( );
}
