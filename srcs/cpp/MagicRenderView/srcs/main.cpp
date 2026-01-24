#include <app/application.h>
#include <widget/colorSlider/colorSlider.h>

#include "testCode/testCodeSources.h"

int main( int argc, char *argv[ ] ) {

	Application app( argc, argv );

	if( app.init( ) == false )
		return -1;
	ColorSlider *cl = new ColorSlider( nullptr );
	cl->show( );
	cl->resize( 500, 500 );
	app.widgetMoveTargetDispyer( cl, 0 );
	if( TestCodeSources::testAll( ) == false )
		return -2;

	int exec = app.exec( );
	return exec;
}
