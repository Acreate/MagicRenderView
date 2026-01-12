#include <app/application.h>
#include <QLibraryInfo>

#include "testCode/testCodeSources.h"

int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );
	if( app.init( ) == false )
		return -1;
	if( TestCodeSources::testAll( ) == false )
		return -2;

	int exec = app.exec( );
	return exec;
}
