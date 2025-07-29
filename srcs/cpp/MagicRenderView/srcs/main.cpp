#include "qt/application/application.h"
#include "qt/mainWindows/mainWindow.h"
#include "qt/stacks/funStack/IFunStack.h"
#include "qt/stacks/varStack/IVarStack.h"
#include "qt/tools/tools.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );
	
	if( IVarStack::init( ) == false ) {
		tools::debug::printError( "无法初始化变量堆栈 : IVarStack::init( ) -> false" );
		return -1;
	}
	if( IFunStack::init( ) == false ) {
		tools::debug::printError( "无法初始化函数堆栈 : IFunStack::init( ) -> false" );
		return -2;
	}


	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
