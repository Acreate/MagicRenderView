#include "qt/application/application.h"
#include "qt/mainWindow/mainWindow.h"
#include "qt/tools/tools.h"
#include "qt/type/baseType/intTypeObject.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );

	IntTypeObject d( 10 );
	tools::debug::printError( d.toString( ) );
	int var = 45;
	tools::debug::printError( QString::number( var ) );
	var = d;
	tools::debug::printError( QString::number( var ) );
	d = 12;
	tools::debug::printError( d.toString( ) );
	return app.exec( );
}
