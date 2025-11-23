#include <app/application.h>

#include <win/mainWindow.h>

#include "app/printfInfo.h"

#include "type/varGenerate.h"
#include "type/stack/unity/float32UnityStack.h"
template< typename TTestType >
void testVarGener( const TTestType &default_var ) {
	auto instancePtr = Application::getInstancePtr( );
	auto varGenerate = instancePtr->getVarGenerate( );
	auto checkVar = varGenerate->create< TTestType >( );
	if( checkVar ) {
		*checkVar = default_var;
		qDebug( ) << "序列化值:" << *checkVar;
		std::vector< uint8_t > buff;
		uint64_t count = varGenerate->toVector( checkVar, buff );
		if( count ) {
			void *converPtr = nullptr;
			count = varGenerate->toVar( buff.data( ), buff.size( ), converPtr );
			if( count ) {
				auto castPtr = varGenerate->cast_ptr< TTestType >( converPtr );
				qDebug( ) << "反序列化:" << *castPtr;
			} else
				instancePtr->getPrintfInfo( )->error( QString( "反序列哈失败 " ) + typeid( TTestType ).name( ) );
		} else
			instancePtr->getPrintfInfo( )->error( QString( "序列化失败 " ) + typeid( TTestType ).name( ) );
	} else
		instancePtr->getPrintfInfo( )->error( QString( "创建失败 " ) + typeid( TTestType ).name( ) );
	qDebug( ) << "";
}
void testVarGener( ) {
	testVarGener< float >( 155.2 );
	testVarGener< double >( 255.1 );
	testVarGener< int8_t >( 255.1 );
	testVarGener< int16_t >( 255.1 );
	testVarGener< int32_t >( 255.1 );
	testVarGener< int64_t >( 255.1 );
	testVarGener< uint8_t >( 255.1 );
	testVarGener< uint16_t >( -255.1 );
	testVarGener< uint32_t >( -255.1 );
	testVarGener< uint64_t >( -255.1 );
	testVarGener< QString >( "255.1" );
}
int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false )
		return -1;
	testVarGener( );
	MainWindow mainwidget;
	mainwidget.show( );

	int exec = app.exec( );
	return exec;
}
