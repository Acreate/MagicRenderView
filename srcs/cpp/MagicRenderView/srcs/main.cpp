#include "qt/application/application.h"
#include "qt/generate/varTypeGenerate.h"
#include "qt/widgets/mainWidget.h"
#include "qt/windows/mainWindow.h"

int testQStringSerialization( ) {

	std_vector< uint8_t > buff;
	QString ceshi1 = "QString 12345";
	QString ceshi2;
	BinGenerate::toBin( ceshi1, buff );
	BinGenerate::toObj( &ceshi2, buff.data( ), buff.size( ) );
	qDebug( ) << "--------------";
	qDebug( ) << ceshi1;
	qDebug( ) << ceshi2;
	qDebug( ) << "--------------";
	//return 0;
	std_vector< QString > ceshiv1;
	ceshiv1.emplace_back( "std_vector< QString > 123123" );
	ceshiv1.emplace_back( "std_vector< QString > 778" );
	ceshiv1.emplace_back( "std_vector< QString > 90" );
	std_vector< QString > ceshiv2;
	BinGenerate::toBin( ceshiv1, buff );
	BinGenerate::toObj( &ceshiv2, buff.data( ), buff.size( ) );
	qDebug( ) << "--------------";
	qDebug( ) << ceshiv1;
	qDebug( ) << ceshiv2;
	qDebug( ) << "--------------";
	std_vector< QString * > ceshivp1;
	ceshivp1.emplace_back( new QString( "std_vector< QString * > 123123" ) );
	ceshivp1.emplace_back( new QString( "std_vector< QString * > 778" ) );
	ceshivp1.emplace_back( new QString( "std_vector< QString * > 90" ) );
	std_vector< QString * > ceshivp2;
	BinGenerate::toBin( ceshivp1, buff );
	BinGenerate::toObj( &ceshivp2, buff.data( ), buff.size( ) );
	qDebug( ) << "--------------";
	for( auto item : ceshivp1 )
		qDebug( ) << *item;
	for( auto item : ceshivp2 )
		qDebug( ) << *item;
	qDebug( ) << "--------------";

	/*return 0;*/
	auto mkVarTypeGeneratePair = VarTypeGenerate::templateVarType< QString >( );
	mkVarTypeGeneratePair->appendUnity( "first" );
	mkVarTypeGeneratePair->appendUnity( "mid" );
	mkVarTypeGeneratePair->appendUnity( "end" );
	auto data = mkVarTypeGeneratePair->data< QString >( );
	size_t count = mkVarTypeGeneratePair->size( );
	if( data == nullptr ) {
		tools::debug::printError( "无法追加元素" );
		return 0;
	}
	qDebug( ) << "--------------";
	qDebug( ) << "\rtype::" << mkVarTypeGeneratePair->getUnityTypeName( );
	for( size_t index = 0; index < count; ++index )
		qDebug( ) << *data[ index ];
	qDebug( ) << "--------------";

	buff = VarTypeGenerate::toBin( mkVarTypeGeneratePair );
	auto var = VarTypeGenerate::toObj( count, buff.data( ), buff.size( ) );
	if( var == nullptr ) {
		tools::debug::printError( "加载对象失败" );
		return 0;
	}
	qDebug( ) << "--------------";
	qDebug( ) << "\rtype::" << var->getUnityTypeName( );
	data = var->data< QString >( );
	if( data == nullptr )
		return 0;
	count = var->size( );
	for( size_t index = 0; index < count; ++index ) {
		QString *string = data[ index ];
		if( string )
			qDebug( ) << *string;
		else
			qDebug( ) << "序列 : [ " << index << " ]为空";
	}
	qDebug( ) << "--------------";
	return 0;
}

void testIntSerialization( ) {

	std_vector< uint8_t > buff;
	uint16_t ceshi1 = 85;
	uint16_t ceshi2 = 0;

	BinGenerate::toBin( ceshi1, buff );
	BinGenerate::toObj( &ceshi2, buff.data( ), buff.size( ) );
	qDebug( ) << "--------------";
	qDebug( ) << ceshi1;
	qDebug( ) << ceshi2;
	qDebug( ) << "--------------";
	//return 0;
	std_vector< uint16_t > ceshiv1;
	ceshiv1.emplace_back( 123 );
	ceshiv1.emplace_back( 456 );
	ceshiv1.emplace_back( 789 );
	std_vector< uint16_t > ceshiv2;
	BinGenerate::toBin( ceshiv1, buff );
	BinGenerate::toObj( &ceshiv2, buff.data( ), buff.size( ) );
	qDebug( ) << "--------------";
	qDebug( ) << ceshiv1;
	qDebug( ) << ceshiv2;
	qDebug( ) << "--------------";
	std_vector< uint16_t * > ceshivp1;
	ceshivp1.emplace_back( new uint16_t( 98 ) );
	ceshivp1.emplace_back( new uint16_t( 87 ) );
	ceshivp1.emplace_back( new uint16_t( 765 ) );
	std_vector< uint16_t * > ceshivp2;
	BinGenerate::toBin( ceshivp1, buff );
	BinGenerate::toObj( &ceshivp2, buff.data( ), buff.size( ) );
	qDebug( ) << "--------------";
	for( auto item : ceshivp1 )
		qDebug( ) << *item;
	for( auto item : ceshivp2 )
		qDebug( ) << *item;
	qDebug( ) << "--------------";

	/*return 0;*/
	auto mkVarTypeGeneratePair = VarTypeGenerate::templateVarType< uint16_t >( );
	mkVarTypeGeneratePair->appendUnity< uint16_t >( 13 );
	mkVarTypeGeneratePair->appendUnity< uint16_t >( 45 );
	mkVarTypeGeneratePair->appendUnity< uint16_t >( 99 );
	auto data = mkVarTypeGeneratePair->data< uint16_t >( );
	size_t count = mkVarTypeGeneratePair->size( );
	if( data == nullptr ) {
		tools::debug::printError( "无法追加元素" );
		return;
	}
	qDebug( ) << "--------------";
	qDebug( ) << "\rtype::" << mkVarTypeGeneratePair->getUnityTypeName( );
	for( size_t index = 0; index < count; ++index )
		qDebug( ) << *data[ index ];
	qDebug( ) << "--------------";

	buff = VarTypeGenerate::toBin( mkVarTypeGeneratePair );
	auto var = VarTypeGenerate::toObj( count, buff.data( ), buff.size( ) );
	if( var == nullptr ) {
		tools::debug::printError( "加载对象失败" );
		return;
	}
	qDebug( ) << "--------------";
	qDebug( ) << "\rtype::" << var->getUnityTypeName( );
	data = var->data< uint16_t >( );
	if( data == nullptr )
		return;
	count = var->size( );
	for( size_t index = 0; index < count; ++index ) {
		uint16_t *string = data[ index ];
		if( string )
			qDebug( ) << *string;
		else
			qDebug( ) << "序列 : [ " << index << " ]为空";
	}
	qDebug( ) << "--------------";
	return;
}
void testQtSerialization( ) {
	std_vector< uint8_t > buff;
	QColor color( 234, 12, 24, 4 );
	qDebug( ) << color;
	BinGenerate::toBin( color, buff );
	QColor color2;
	BinGenerate::toObj( &color2, buff.data( ), buff.size( ) );
	qDebug( ) << color2;

	QImage image;
	image.load( ":/ico/play_error.png" );
	image.save( "./image1.png" );
	BinGenerate::toBin( image, buff );
	QImage image2;
	BinGenerate::toObj( &image2, buff.data( ), buff.size( ) );
	image2.save( "./image2.png" );
}
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );
	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
