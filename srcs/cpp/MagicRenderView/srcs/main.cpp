#include "qt/application/application.h"
#include "qt/generate/varTypeGenerate.h"
#include "qt/windows/mainWindow.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );
	auto supperTypes = VarTypeGenerate::supperTypes( );
	qDebug( ) << supperTypes;
	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
