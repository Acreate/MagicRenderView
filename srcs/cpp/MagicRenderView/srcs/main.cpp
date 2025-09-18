#include "qt/application/application.h"
#include "qt/generate/varTypeGenerate.h"
#include "qt/windows/mainWindow.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );


	auto templateVarType = VarTypeGenerate::templateVarType<QString>(  nullptr );
	templateVarType->appendUnity( "45487" );
	auto stdVector = templateVarType->toBin(  );
	qDebug() << *templateVarType->data<QString>(  )[0];
	auto templateVarType2 = VarTypeGenerate::templateVarType<QString>(  nullptr );
	templateVarType2->loadBin( stdVector );
	qDebug() << *templateVarType2->data<QString>(  )[0];
	MainWindow mainwidget;
	mainwidget.show( );
	return app.exec( );
}
