#include "application.h"

#include "../director/nodeDirector.h"
#include "../director/printerDirector.h"
#include "../director/varDirector.h"

#include "../win/mainWindow.h"

Application *Application::instance = nullptr;
Application * Application::getInstancePtr( ) {
	return instance;
}

Application::Application( int &argc, char **const argv, const int i ) : QApplication( argc, argv, i ) {
}
Application::~Application( ) {
	delete nodeDirector;
	delete printerDirector;
	delete varDirector;
}
bool Application::init( ) {
	Application::instance = this;
	printerDirector = new PrinterDirector;
	varDirector = new VarDirector;
	nodeDirector = new NodeDirector;
	mainWindow = new MainWindow( );
	if( printerDirector->init( ) == false )
		return false;
	if( varDirector->init( ) == false )
		return false;
	if( nodeDirector->init( ) == false )
		return false;
	if( mainWindow->init( ) == false )
		return false;
	return true;
}
