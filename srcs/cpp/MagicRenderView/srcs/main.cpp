#include <qfile.h>

#include "qt/application/application.h"
#include "qt/generate/varGenerate.h"
#include "qt/widgets/mainWidget.h"
#include "qt/windows/mainWindow.h"

#define out_start() qDebug() << "\n\n开始 ====\t" << tools::debug::getFunctionName( )[ 0 ] << "\n\n";
#define out_end() qDebug() << "\n\n结束 ====" << tools::debug::getFunctionName( )[ 0 ]

void test( ) {
	out_start( );
	out_end( );
}
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );
	if( app.init( ) == false ) {
		tools::debug::printError( "程序初始化失败" );
		return -1;
	}
	test( );
	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
