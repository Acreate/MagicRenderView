#include <app/application.h>

#include <win/mainWindow.h>

#include "app/printfInfo.h"

#include "type/varGenerate.h"
#include "type/stack/unity/float32UnityStack.h"
template< typename TTestType >
void testVarGener( const TTestType &default_var ) {
	auto name = typeid( TTestType ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
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
				instancePtr->getPrintfInfo( )->error( QString( "反序列哈失败 " ) + name );
		} else
			instancePtr->getPrintfInfo( )->error( QString( "序列化失败 " ) + name );
	} else
		instancePtr->getPrintfInfo( )->error( QString( "创建失败 " ) + name );
	qDebug( ) << "";
}

template< typename TTestFirstType, typename TTestScondType >
void testPairVarGener( const TTestFirstType &first_var_value, const TTestScondType &scond_var_varlue ) {
	auto name = typeid( std::pair< void *, void * > ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varGenerate = instancePtr->getVarGenerate( );
	auto checkVar = varGenerate->create< std::pair< void *, void * > >( );
	if( checkVar ) {
		auto first = varGenerate->create< TTestFirstType >( );
		auto scond = varGenerate->create< TTestScondType >( );
		*first = first_var_value;
		*scond = scond_var_varlue;
		checkVar->first = first;
		checkVar->second = scond;
		qDebug( ) << "序列化值:" << *first << ", " << *scond;
		std::vector< uint8_t > buff;
		uint64_t count = varGenerate->toVector( checkVar, buff );
		if( count ) {
			void *converPtr = nullptr;
			count = varGenerate->toVar( buff.data( ), buff.size( ), converPtr );
			if( count ) {
				auto castPtr = varGenerate->cast_ptr< std::pair< void *, void * > >( converPtr );
				first = varGenerate->cast_ptr< int32_t >( castPtr->first );
				scond = varGenerate->cast_ptr< QString >( castPtr->second );
				qDebug( ) << "反序列化:" << *first << ", " << *scond;
			} else
				instancePtr->getPrintfInfo( )->error( QString( "反序列哈失败 " ) + name );
		} else
			instancePtr->getPrintfInfo( )->error( QString( "序列化失败 " ) + name );
	} else
		instancePtr->getPrintfInfo( )->error( QString( "创建失败 " ) + name );
	qDebug( ) << "";
}

template< typename TTestFirstType >
void testArrayVarGener( const TTestFirstType &first_var_value, const size_t &array_count ) {
	auto name = typeid( std::vector< TTestFirstType > ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varGenerate = instancePtr->getVarGenerate( );
	auto checkVar = varGenerate->create< std::vector< TTestFirstType > >( );
	if( checkVar ) {
		checkVar->resize( array_count, first_var_value );
		QStringList data;
		auto arrayDataPtr = checkVar->data( );
		for( size_t index = 0; index < array_count; ++index )
			data.append( QString( "%1" ).arg( arrayDataPtr[ index ] ) );
		qDebug( ) << "序列化值:" << data.join( ", " );
		std::vector< uint8_t > buff;
		uint64_t count = varGenerate->toVector( checkVar, buff );
		if( count ) {
			void *converPtr = nullptr;
			count = varGenerate->toVar( buff.data( ), buff.size( ), converPtr );
			if( count ) {
				data.clear( );
				auto castPtr = varGenerate->cast_ptr< std::vector< TTestFirstType > >( converPtr );
				arrayDataPtr = castPtr->data( );
				for( size_t index = 0; index < array_count; ++index )
					data.append( QString( "%1" ).arg( arrayDataPtr[ index ] ) );
				qDebug( ) << "反序列化:" << data.join( ", " );
			} else
				instancePtr->getPrintfInfo( )->error( QString( "反序列哈失败 " ) + name );
		} else
			instancePtr->getPrintfInfo( )->error( QString( "序列化失败 " ) + name );
	} else
		instancePtr->getPrintfInfo( )->error( QString( "创建失败 " ) + name );
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
	testPairVarGener< int32_t, QString >( 0, "" );
	testPairVarGener< int32_t, QString >( 888, "323" );
	testArrayVarGener< float >( 155.2, 5 );
	testArrayVarGener< double >( 255.1, 5 );
	testArrayVarGener< uint8_t >( -547, 5 );
	testArrayVarGener< uint16_t >( -547, 5 );
	testArrayVarGener< uint32_t >( -547, 5 );
	testArrayVarGener< uint64_t >( -547, 5 );
	testArrayVarGener< int8_t >( 547, 5 );
	testArrayVarGener< int16_t >( 547, 5 );
	testArrayVarGener< int32_t >( 547, 5 );
	testArrayVarGener< int64_t >( 547, 5 );
	testArrayVarGener< QString >( "547", 5 );
}
int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false )
		return -1;
	testVarGener( );
	return 0;
	MainWindow mainwidget;
	mainwidget.show( );

	int exec = app.exec( );
	return exec;
}
