#include "testCodeSources.h"
#include <QDebug>

#include "../app/application.h"

#include "../director/printerDirector.h"
#include "../director/varDirector.h"

template< typename TTestType >
void testVarGener( const TTestType &default_var ) {
	auto name = typeid( TTestType ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varDirector = instancePtr->getVarDirector( );
	auto checkVar = varDirector->create< TTestType >( );
	if( checkVar ) {
		*checkVar = default_var;
		qDebug( ) << "序列化值:" << *checkVar;
		std::vector< uint8_t > buff;
		uint64_t count = varDirector->toVector( checkVar, buff );
		if( count ) {
			void *converPtr = nullptr;
			count = varDirector->toVar( buff.data( ), buff.size( ), converPtr );
			if( count ) {
				auto castPtr = varDirector->cast_ptr< TTestType >( converPtr );
				qDebug( ) << "反序列化:" << *castPtr;
			} else
				instancePtr->getPrinterDirector( )->error( QString( "反序列哈失败 " ) + name );
		} else
			instancePtr->getPrinterDirector( )->error( QString( "序列化失败 " ) + name );
	} else
		instancePtr->getPrinterDirector( )->error( QString( "创建失败 " ) + name );
	qDebug( ) << "";
}

template< typename TTestFirstType, typename TTestScondType >
void testPairVarGener( const TTestFirstType &first_var_value, const TTestScondType &scond_var_varlue ) {
	auto name = typeid( std::pair< void *, void * > ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varDirector = instancePtr->getVarDirector( );
	auto checkVar = varDirector->create< std::pair< void *, void * > >( );
	if( checkVar ) {
		auto first = varDirector->create< TTestFirstType >( );
		auto scond = varDirector->create< TTestScondType >( );
		*first = first_var_value;
		*scond = scond_var_varlue;
		checkVar->first = first;
		checkVar->second = scond;
		qDebug( ) << "序列化值:" << *first << ", " << *scond;
		std::vector< uint8_t > buff;
		uint64_t count = varDirector->toVector( checkVar, buff );
		if( count ) {
			void *converPtr = nullptr;
			count = varDirector->toVar( buff.data( ), buff.size( ), converPtr );
			if( count ) {
				auto castPtr = varDirector->cast_ptr< std::pair< void *, void * > >( converPtr );
				first = varDirector->cast_ptr< int32_t >( castPtr->first );
				scond = varDirector->cast_ptr< QString >( castPtr->second );
				qDebug( ) << "反序列化:" << *first << ", " << *scond;
			} else
				instancePtr->getPrinterDirector( )->error( QString( "反序列哈失败 " ) + name );
		} else
			instancePtr->getPrinterDirector( )->error( QString( "序列化失败 " ) + name );
	} else
		instancePtr->getPrinterDirector( )->error( QString( "创建失败 " ) + name );
	qDebug( ) << "";
}

template< typename TTestFirstType >
void testArrayVarGener( const TTestFirstType &first_var_value, const size_t &array_count ) {
	auto name = typeid( std::vector< TTestFirstType > ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varDirector = instancePtr->getVarDirector( );
	auto checkVar = varDirector->create< std::vector< TTestFirstType > >( );
	if( checkVar ) {
		checkVar->resize( array_count, first_var_value );
		QStringList data;
		auto arrayDataPtr = checkVar->data( );
		for( size_t index = 0; index < array_count; ++index )
			data.append( QString( "%1" ).arg( arrayDataPtr[ index ] ) );
		qDebug( ) << "序列化值:" << data.join( ", " );
		std::vector< uint8_t > buff;
		uint64_t count = varDirector->toVector( checkVar, buff );
		if( count ) {
			void *converPtr = nullptr;
			count = varDirector->toVar( buff.data( ), buff.size( ), converPtr );
			if( count ) {
				data.clear( );
				auto castPtr = varDirector->cast_ptr< std::vector< TTestFirstType > >( converPtr );
				arrayDataPtr = castPtr->data( );
				for( size_t index = 0; index < array_count; ++index )
					data.append( QString( "%1" ).arg( arrayDataPtr[ index ] ) );
				qDebug( ) << "反序列化:" << data.join( ", " );
			} else
				instancePtr->getPrinterDirector( )->error( QString( "反序列哈失败 " ) + name );
		} else
			instancePtr->getPrinterDirector( )->error( QString( "序列化失败 " ) + name );
	} else
		instancePtr->getPrinterDirector( )->error( QString( "创建失败 " ) + name );
	qDebug( ) << "";
}

template< typename TTestFirstType >
void testAnyArrayVarGener( const TTestFirstType &first_var_value, const size_t &array_count ) {
	auto name = typeid( std::vector< void * > ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varDirector = instancePtr->getVarDirector( );
	auto checkVar = varDirector->create< std::vector< void * > >( );
	if( checkVar ) {
		checkVar->resize( array_count, nullptr );
		QStringList data;
		auto arrayDataPtr = checkVar->data( );
		for( size_t index = 0; index < array_count; ++index ) {
			auto unityVar = varDirector->create< TTestFirstType >( );
			if( unityVar == nullptr ) {
				auto name = typeid( std::vector< void * > ).name( );
				qDebug( ) << "单元创建失败:" << name;
				return;
			}
			*unityVar = first_var_value;
			arrayDataPtr[ index ] = unityVar;
			data.append( QString( "%1" ).arg( *unityVar ) );
		}
		qDebug( ) << "序列化值:" << data.join( ", " );
		std::vector< uint8_t > buff;
		uint64_t count = varDirector->toVector( checkVar, buff );
		if( count ) {
			void *converPtr = nullptr;
			count = varDirector->toVar( buff.data( ), buff.size( ), converPtr );
			if( count ) {
				data.clear( );
				auto castPtr = varDirector->cast_ptr< std::vector< void * > >( converPtr );
				arrayDataPtr = castPtr->data( );
				for( size_t index = 0; index < array_count; ++index ) {
					auto unityVar = varDirector->cast_ptr< TTestFirstType >( arrayDataPtr[ index ] );
					if( unityVar == nullptr ) {
						auto name = typeid( std::vector< void * > ).name( );
						qDebug( ) << "单元转换失败:" << name;
						return;
					}
					data.append( QString( "%1" ).arg( *unityVar ) );
				}
				qDebug( ) << "反序列化:" << data.join( ", " );
			} else
				instancePtr->getPrinterDirector( )->error( QString( "反序列哈失败 " ) + name );
		} else
			instancePtr->getPrinterDirector( )->error( QString( "序列化失败 " ) + name );
	} else
		instancePtr->getPrinterDirector( )->error( QString( "创建失败 " ) + name );
	qDebug( ) << "";
}

void TestCodeSources::testVarGener( ) {
	::testVarGener< float >( 155.2 );
	::testVarGener< double >( 255.1 );
	::testVarGener< int8_t >( 255.1 );
	::testVarGener< int16_t >( 255.1 );
	::testVarGener< int32_t >( 255.1 );
	::testVarGener< int64_t >( 255.1 );
	::testVarGener< uint8_t >( 255.1 );
	::testVarGener< uint16_t >( -255.1 );
	::testVarGener< uint32_t >( -255.1 );
	::testVarGener< uint64_t >( -255.1 );
	::testVarGener< QString >( "255.1，含糊" );
	::testPairVarGener< int32_t, QString >( 0, "" );
	::testPairVarGener< int32_t, QString >( 888, "323" );
	::testPairVarGener< int32_t, QString >( 888, "323汉文化" );
	::testArrayVarGener< float >( 155.2, 5 );
	::testArrayVarGener< double >( 255.1, 5 );
	::testArrayVarGener< uint8_t >( -547, 5 );
	::testArrayVarGener< uint16_t >( -547, 5 );
	::testArrayVarGener< uint32_t >( -547, 5 );
	::testArrayVarGener< uint64_t >( -547, 5 );
	::testArrayVarGener< int8_t >( 547, 5 );
	::testArrayVarGener< int16_t >( 547, 5 );
	::testArrayVarGener< int32_t >( 547, 5 );
	::testArrayVarGener< int64_t >( 547, 5 );
	::testArrayVarGener< QString >( "547", 5 );
	::testAnyArrayVarGener< QString >( "", 5 );
	::testAnyArrayVarGener< QString >( "985单元", 5 );
}
