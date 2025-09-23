#include <qfile.h>

#include "qt/application/application.h"
#include "qt/generate/binGenerate.h"
#include "qt/generate/varGenerate.h"
#include "qt/varType/typds/floatType.h"
#include "qt/varType/typds/nullptrType.h"
#include "qt/varType/typds/stringType.h"
#include "qt/widgets/mainWidget.h"
#include "qt/windows/mainWindow.h"

#define out_start() qDebug() << "\n\n开始 ====\t" << tools::debug::getFunctionName( )[ 0 ]
#define out_end() qDebug() << "结束 ====\t" << tools::debug::getFunctionName( )[ 0 ]
int testQStringSerialization( ) {
	out_start( );

	do {
		std_vector< uint8_t > buff;
		QString ceshi1 = "QString 12345";
		QString ceshi2;
		BinGenerate::toBin( ceshi1, buff );
		BinGenerate::toObj( &ceshi2, buff.data( ), buff.size( ) );
		qDebug( ) << "------	QString		--------";
		qDebug( ) << ceshi1;
		qDebug( ) << "-----		反序列输出";
		qDebug( ) << ceshi2;
		qDebug( ) << "--------------";
		return 0;
		std_vector< QString > ceshiv1;
		ceshiv1.emplace_back( "std_vector< QString > 123123" );
		ceshiv1.emplace_back( "std_vector< QString > 778" );
		ceshiv1.emplace_back( "std_vector< QString > 90" );
		std_vector< QString > ceshiv2;
		BinGenerate::toBin( ceshiv1, buff );
		BinGenerate::toObj( &ceshiv2, buff.data( ), buff.size( ) );
		qDebug( ) << "------	std_vector< QString >	--------";
		qDebug( ) << ceshiv1;
		qDebug( ) << "-----		反序列输出";
		qDebug( ) << ceshiv2;
		qDebug( ) << "--------------";
		std_vector< QString * > ceshivp1;
		ceshivp1.emplace_back( new QString( "std_vector< QString * > 123123" ) );
		ceshivp1.emplace_back( new QString( "std_vector< QString * > 778" ) );
		ceshivp1.emplace_back( new QString( "std_vector< QString * > 90" ) );
		std_vector< QString * > ceshivp2;
		BinGenerate::toBin( ceshivp1, buff );
		BinGenerate::toObj( &ceshivp2, buff.data( ), buff.size( ) );
		qDebug( ) << "------	std_vector< QString * >	--------";
		for( auto item : ceshivp1 ) {
			qDebug( ) << *item;
			delete item;
		}
		qDebug( ) << "-----		反序列输出";
		for( auto item : ceshivp2 ) {
			qDebug( ) << *item;
			delete item;
		}
		qDebug( ) << "--------------";

		qDebug( ) << "--------------";
	} while( false );
	out_end( );
	return 0;
}

void testIntSerialization( ) {
	out_start( );
	do {
		std_vector< uint8_t > buff;
		uint16_t ceshi1 = 85;
		uint16_t ceshi2 = 0;

		BinGenerate::toBin( ceshi1, buff );
		BinGenerate::toObj( &ceshi2, buff.data( ), buff.size( ) );
		qDebug( ) << "--------------";
		qDebug( ) << ceshi1;
		qDebug( ) << "-----		反序列输出";
		qDebug( ) << ceshi2;
		qDebug( ) << "--------------";
		std_vector< uint16_t > ceshiv1;
		ceshiv1.emplace_back( 123 );
		ceshiv1.emplace_back( 456 );
		ceshiv1.emplace_back( 789 );
		std_vector< uint16_t > ceshiv2;
		BinGenerate::toBin( ceshiv1, buff );
		BinGenerate::toObj( &ceshiv2, buff.data( ), buff.size( ) );
		qDebug( ) << "--------------";
		qDebug( ) << ceshiv1;
		qDebug( ) << "-----		反序列输出";
		qDebug( ) << ceshiv2;
		qDebug( ) << "--------------";
		std_vector< uint16_t * > ceshivp1;
		ceshivp1.emplace_back( new uint16_t( 98 ) );
		ceshivp1.emplace_back( new uint16_t( 87 ) );
		ceshivp1.emplace_back( new uint16_t( 765 ) );
		std_vector< uint16_t * > ceshivp2;
		BinGenerate::toBin( ceshivp1, buff );
		BinGenerate::toObj( &ceshivp2, buff.data( ), buff.size( ) );
		qDebug( ) << "------	std_vector< uint16_t * >	--------";
		for( auto item : ceshivp1 ) {
			qDebug( ) << *item;
			delete item;
		}
		qDebug( ) << "-----		反序列输出";
		for( auto item : ceshivp2 ) {
			qDebug( ) << *item;
			delete item;
		}
		qDebug( ) << "--------------";

	} while( false );
	out_end( );

}
void testQtSerialization( ) {
	out_start( );
	do {
		std_vector< uint8_t > buff;
		QColor color( 234, 12, 24, 4 );
		qDebug( ) << color;
		BinGenerate::toBin( color, buff );
		QColor color2;
		BinGenerate::toObj( &color2, buff.data( ), buff.size( ) );
		qDebug( ) << color2;

		QImage image;
		image.load( ":/ico/play_error.png" );
		QFile::remove( "./image1.png" );
		image.save( "./image1.png" );
		BinGenerate::toBin( image, buff );
		QImage image2;
		BinGenerate::toObj( &image2, buff.data( ), buff.size( ) );
		QFile::remove( "./image2.png" );
		image2.save( "./image2.png" );
	} while( false );
	out_end( );
}
void testAppType( ) {
	out_start( );

	FloatType *float1 = VarGenerate::createVarType< FloatType >( );
	FloatType *float2 = VarGenerate::createVarType< FloatType >( );
	StringType *str = VarGenerate::createVarType< StringType >( );
	*float1 = *float1 + *float2;
	*float1 = *float1 + *str;
	*float1 = *str;

	NullptrType *null = VarGenerate::createVarType< NullptrType >( );
	if( *null == *float1 )
		qDebug( ) << "类型等于空";
	else
		qDebug( ) << "类型不等于空";

	BaseVarType *varType = VarGenerate::createVarType< FloatType >( );
	auto p = qobject_cast< FloatType * >( varType );
	qDebug( ) << "类型转换 : " << p;
	delete float1;
	delete float2;
	delete varType;
	out_end( );
}
void test( ) {

	testQStringSerialization( );
	testIntSerialization( );
	testQtSerialization( );
	testAppType( );
}
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );
	test( );
	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
