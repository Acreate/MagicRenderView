#include <qfile.h>

#include "qt/application/application.h"
#include "qt/generate/binGenerate.h"
#include "qt/generate/varGenerate.h"
#include "qt/widgets/mainWidget.h"
#include "qt/windows/mainWindow.h"

#define out_start() qDebug() << "\n\n开始 ====\t" << tools::debug::getFunctionName( )[ 0 ] << "\n\n";
#define out_end() qDebug() << "\n\n结束 ====" << tools::debug::getFunctionName( )[ 0 ]

template< typename ttype >
void serType( const ttype &test_var ) {
	auto varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
	size_t result = 0;
	std_vector< uint8_t > buff;
	const void *targetPtr = &test_var;
	const auto &targetTypeInfo = typeid( test_var );
	if( varGenerate->toBinVector( targetTypeInfo, targetPtr, buff, result ) == true ) {
		ttype testSize;
		varGenerate->toOBjVector( targetTypeInfo, &testSize, result, buff.data( ), buff.size( ) );
		auto stdVector = tools::debug::getFunctionName( 4 );
		qDebug( ) << stdVector[ 1 ] << " : " << testSize;
	} else
		tools::debug::printError( QString( "%1 类型失败" ).arg( targetTypeInfo.name( ) ) );
}

template< >
void serType( const std::string &test_var ) {
	auto varGenerate = Application::getApplicationInstancePtr( )->getVarGenerate( );
	size_t result = 0;
	std_vector< uint8_t > buff;
	const void *targetPtr = &test_var;
	const auto &targetTypeInfo = typeid( test_var );
	if( varGenerate->toBinVector( targetTypeInfo, targetPtr, buff, result ) == true ) {
		std::string testSize;
		varGenerate->toOBjVector( targetTypeInfo, &testSize, result, buff.data( ), buff.size( ) );
		auto stdVector = tools::debug::getFunctionName( 4 );
		qDebug( ) << stdVector[ 1 ] << " : " << testSize.c_str(  );
	} else
		tools::debug::printError( QString( "%1 类型失败" ).arg( targetTypeInfo.name( ) ) );
}
void test( ) {
	out_start( );
	uint64_t test1 = 64;
	serType( test1 );
	uint32_t test2 = 32;
	serType( test2 );
	uint16_t test3 = 16;
	serType( test3 );
	uint8_t test4 = 8;
	serType( test4 );

	int64_t test10 = -64;
	serType( test10 );
	int32_t test20 = -32;
	serType( test20 );
	int16_t test30 = -16;
	serType( test30 );
	int8_t test40 = -8;
	serType( test40 );

	float floatTest = -48.15;
	serType( floatTest );

	double doubleTest = 48.15;
	serType( doubleTest );

	QString buff = "这生意";
	serType( buff );

	std::string buff1 = "这生意std::string";
	serType( buff1 );

	std::wstring buff2 = L"这生意std::wstring";
	serType( buff2 );

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
