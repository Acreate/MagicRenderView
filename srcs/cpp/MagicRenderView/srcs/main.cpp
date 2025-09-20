#include "qt/application/application.h"
#include "qt/generate/varTypeGenerate.h"
#include "qt/windows/mainWindow.h"

int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	auto mkVarTypeGeneratePair = VarTypeGenerate::templateVarType< QString >( );
	mkVarTypeGeneratePair->appendUnity( "first" );
	mkVarTypeGeneratePair->appendUnity( "mid" );
	mkVarTypeGeneratePair->appendUnity( "end" );
	auto data = mkVarTypeGeneratePair->data< QString >( );
	size_t count = mkVarTypeGeneratePair->size( );
	if( data == nullptr )
		return 0;
	qDebug( ) << "--------------";
	qDebug( ) << "\rtype::" << mkVarTypeGeneratePair->getUnityTypeName( );
	for( size_t index = 0; index < count; ++index )
		qDebug( ) << *data[ index ];
	qDebug( ) << "--------------";
	std_vector< uint8_t > buff;
	VarTypeGenerate::toBin( mkVarTypeGeneratePair, buff );
	auto var = VarTypeGenerate::toObj( count, buff.data( ), buff.size( ) );
	if( var == nullptr )
		return 0;
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
	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
