#include <qfile.h>

#include "qt/application/application.h"
#include "qt/generate/varGenerate.h"
#include "qt/tools/tools.h"
#include "qt/widgets/mainWidget.h"
#include "qt/windows/mainWindow.h"

void test( ) {


	auto varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
	QColor test( 111, 125, 42, 3 );
	qDebug( ) << test;
	std_vector< uint8_t > buff;
	size_t resultCount;
	varGenerate->toBinVector( typeid( QColor ), &test, buff, resultCount );
	QColor test2( 0, 0, 0, 0 );
	varGenerate->toOBjVector( typeid( QColor ), &test2, resultCount, buff.data( ), buff.size( ) );
	qDebug( ) << test;
	qDebug( ) << test2;
}
int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false ) {
		tools::debug::printError( "程序初始化失败" );
		return -1;
	}
	test( );
	return 0;
	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
