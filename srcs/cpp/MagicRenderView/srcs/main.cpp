#include <qfile.h>

#include "qt/application/application.h"
#include "qt/tools/tools.h"
#include "qt/windows/mainWindow.h"
std_vector< int * > test( std_vector< int * > result ) {

	size_t count = result.size( );
	auto data = result.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		if( *data[ index ] == 0 ) {
			delete data[ index ];
			data[ index ] = nullptr;
		}

	size_t subindex;
	// 查找第一个 nullptr
	for( index = 0; index < count; ++index )
		if( data[ index ] == nullptr ) {
			// 匹配后续的第一个非 nullptr
			subindex = index + 1;
			for( ; subindex < count; ++subindex )
				if( data[ subindex ] != nullptr ) {
					data[ index ] = data[ subindex ];
					data[ subindex ] = nullptr;
					break;
				}
		}
	for( index = 0; index < count; ++index )
		if( data[ index ] == nullptr )
			break;
	if( index != count )
		result.resize( index );
	return result;

}
int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false ) {
		tools::debug::printError( "程序初始化失败" );
		return -1;
	}
	std_vector< int * > nStdVector;
	for( size_t index = 0; index < 50; ++index ) {
		size_t targetNum = ( index > 25 ) ? index : 0;
		nStdVector.emplace_back( new int( targetNum ) );
	}
	auto stdVector = test( nStdVector );
	QStringList intOut;
	for( auto debugNum : nStdVector )
		intOut.append( QString::number( *debugNum ) );
	auto nOut = intOut.join( "," );
	intOut.clear( );
	for( auto debugNum : stdVector ) {
		intOut.append( QString::number( *debugNum ) );
		delete debugNum;
	}
	stdVector.clear( );
	qDebug( ) << "2:->\t" << nOut;
	qDebug( ) << "1:->\t" << intOut.join( "," );

	//MainWindow mainwidget;
	//mainwidget.show( );

	//return app.exec( );
}
