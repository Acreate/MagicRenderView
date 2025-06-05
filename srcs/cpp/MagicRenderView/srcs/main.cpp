#include "qt/application/application.h"
#include "qt/mainWindow/mainWindow.h"
#include "qt/stack/IVarStack.h"
#include "qt/stack/base/baseStack.h"
#include "qt/tools/tools.h"
#include "qt/type/baseType/floatTypeObject.h"
#include "qt/type/baseType/intTypeObject.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );

	FloatTypeObject d( 10 );
	tools::debug::printError( d.toString( ) );
	int var = 45;
	tools::debug::printError( QString::number( var ) );
	var = d;
	tools::debug::printError( QString::number( var ) );
	d = 12;
	tools::debug::printError( d.toString( ) );
	tools::debug::printError( IntTypeObject::staticMetaObject.className( ) );

	auto varStack = IVarStack::getInstance< BaseStack >( );
	auto varStack2 = IVarStack::getInstance< BaseStack >( );
	if( varStack.get( ) == varStack2.get( ) )
		tools::debug::printError( "地址一致" );
	else
		tools::debug::printError( "不是同一个对象" );

	return app.exec( );
}
