#include <app/application.h>
#include <widget/colorEditor/colorEditor.h>

#include "testCode/testCodeSources.h"

int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );

	if( app.init( ) == false )
		return -1;
	ColorEditor *cl = new ColorEditor( nullptr );
	cl->resize( 500, 500 );
	app.widgetMoveTargetDispyer( cl, 0 );
	cl->show( );
	if( TestCodeSources::testAll( ) == false )
		return -2;

	int exec = app.exec( );
	delete cl;
	return exec;
}
