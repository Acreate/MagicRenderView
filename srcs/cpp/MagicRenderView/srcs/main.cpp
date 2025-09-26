#include <qfile.h>

#include "qt/application/application.h"
#include "qt/generate/binGenerate.h"
#include "qt/generate/varGenerate.h"
#include "qt/widgets/mainWidget.h"
#include "qt/windows/mainWindow.h"

#define out_start() qDebug() << "\n\n开始 ====\n\n" << tools::debug::getFunctionName( )[ 0 ]
#define out_end() qDebug() << "\n\n结束 ====" << tools::debug::getFunctionName( )[ 0 ]
void test( ) {
	out_start( );
	auto varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
	size_t count = 777;
	size_t result = 0;
	std_vector< uint8_t > buff;
	size_t *targetPtr = &count;
	if( varGenerate->toBinVector( typeid( size_t ), targetPtr, buff, result ) == true ) {
		count = 9999999;
		varGenerate->toOBjVector( typeid( size_t ), targetPtr, result, buff.data( ), buff.size( ) );
		qDebug( ) << tools::debug::getFunctionName( )[ 0 ] << " : " << count;
	} else
		tools::debug::printError( "size_t 类型失败" );
	out_end( );
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
