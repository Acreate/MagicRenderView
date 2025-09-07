#include "qt/application/application.h"
#include "qt/windows/mainWindow.h"
#include "qt/tools/tools.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );
	
	if( app.getStackManagement( ) == nullptr ) {
		tools::debug::printError( "无法初始化堆栈 : app.getStackManagement( ) == nullptr" );
		return -1;
	}

	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
