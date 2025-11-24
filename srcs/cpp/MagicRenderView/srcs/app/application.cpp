#include "application.h"

#include "../director/nodeDirector.h"
#include "../director/printerDirector.h"
#include "../director/varDirector.h"

#include "../win/mainWindow.h"

Application *Application::instance = nullptr;
Application * Application::getInstancePtr( ) {
	return instance;
}

Application::Application( int &argc, char **argv, int i ) : QApplication( argc, argv, i ) {
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
bool Application::setVar( const QString &var_key, const std::vector< uint8_t > &var_value ) {
	size_t count = iniData.size( );
	auto data = iniData.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].first == var_key ) {
			data[ index ].second = var_value;
			return true;
		}
	iniData.emplace_back( var_key, var_value );
	return true;
}
bool Application::getVar( const QString &result_var_key, std::vector< uint8_t > &result_var_value ) {
	size_t count = iniData.size( );
	auto data = iniData.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].first == result_var_key ) {
			result_var_value = data[ index ].second;
			return true;
		}
	return false;
}
bool Application::removeVar( const QString &result_var_key ) {
	size_t count = iniData.size( );
	auto data = iniData.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].first == result_var_key ) {
			iniData.erase( iniData.begin( ) + index );
			return true;
		}
	return false;
}
