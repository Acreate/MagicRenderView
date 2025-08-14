#include "qt/application/application.h"
#include "qt/mainWindows/mainWindow.h"
#include "qt/tools/tools.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	if( app.getStackManagement( ) != 0 ) {
		tools::debug::printError( "无法初始化堆栈 : Application::initStack( ) != 0" );
		return -1;
	}

	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
