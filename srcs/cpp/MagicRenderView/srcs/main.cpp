#include "qt/application/application.h"
#include "qt/generate/varTypeGenerate.h"
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

class first {
	using new_type = int32_t;
public:
	first( ) {

	}
	virtual void print( ) {
		qDebug( ) << typeid( new_type ).name( );
	}
};
class scond : public first {
	using new_type = first;
public:
	scond( ) = default;
};

int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	scond scond;
	scond.print( );
	return 0;
	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
