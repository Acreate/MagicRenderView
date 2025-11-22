#include <app/application.h>

#include <win/mainWindow.h>

#include "type/varGenerate.h"
#include "type/stack/unity/float32UnityStack.h"

void testVarGener( ) {
	auto instancePtr = Application::getInstancePtr( );
	auto varGenerate = instancePtr->getVarGenerate( );
	auto float32 = varGenerate->create< float >( );
	if( float32 ) {
		*float32 = 154.1;
		std::vector< uint8_t > buff;
		uint64_t count = varGenerate->toVector( float32, buff );
		if( count ) {
			void *converPtr = nullptr;
			count = varGenerate->toVar( buff.data( ), buff.size( ), converPtr );
			if( count ) {
				auto castPtr = varGenerate->cast_ptr< float >( converPtr );
				qDebug( ) << *castPtr;
			}
		}
	}
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
