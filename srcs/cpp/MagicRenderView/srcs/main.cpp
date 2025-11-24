#include <app/application.h>

#include <win/mainWindow.h>

#include "testCode/testCodeSources.h"

int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false )
		return -1;
	TestCodeSources::testVarGener( );

	int exec = app.exec( );
	return exec;
}
