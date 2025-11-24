#include <app/application.h>

#include "testCode/testCodeSources.h"

int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false )
		return -1;
	TestCodeSources::testVarGener( );
	TestCodeSources::testAppSaveBin( );
	int exec = app.exec( );
	return exec;
}
