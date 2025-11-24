#include "application.h"

#include <qfile.h>

#include "../director/iniDirector.h"
#include "../director/nodeDirector.h"
#include "../director/printerDirector.h"
#include "../director/varDirector.h"

#include "../win/mainWindow.h"

Application *Application::instance = nullptr;
Application * Application::getInstancePtr( ) {
	return instance;
}

Application::Application( int &argc, char **argv, int i ) : QApplication( argc, argv, i ), mainWindow( nullptr ), iniDirector( nullptr ), varDirector( nullptr ), printerDirector( nullptr ), nodeDirector( nullptr ) {
}
Application::~Application( ) {
	if( mainWindow )
		delete mainWindow;
	if( nodeDirector )
		delete nodeDirector;
	if( iniDirector )
		delete iniDirector;
	if( varDirector )
		delete varDirector;
	if( printerDirector )
		delete printerDirector;
}
bool Application::init( ) {
	Application::instance = this;

	if( mainWindow )
		delete mainWindow;
	if( nodeDirector )
		delete nodeDirector;
	if( iniDirector )
		delete iniDirector;
	if( varDirector )
		delete varDirector;
	if( printerDirector )
		delete printerDirector;
	
	printerDirector = new PrinterDirector;
	varDirector = new VarDirector;
	iniDirector = new IniDirector;
	nodeDirector = new NodeDirector;
	mainWindow = new MainWindow( );
	if( printerDirector->init( ) == false )
		return false;
	if( varDirector->init( ) == false )
		return false;
	if( iniDirector->init( ) == false )
		return false;
	if( nodeDirector->init( ) == false )
		return false;
	if( mainWindow->init( ) == false )
		return false;
	return true;
}
