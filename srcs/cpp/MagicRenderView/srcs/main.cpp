
#include <qfile.h>

#include "qt/application/application.h"
#include "qt/tools/tools.h"
#include "qt/windows/mainWindow.h"

int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false ) {
		tools::debug::printError( "程序初始化失败" );
		return -1;
	}
	
	MainWindow mainwidget;
	mainwidget.show( );

	return app.exec( );
}
