#include "qt/application/application.h"
#include "qt/mainWindow/mainWindow.h"
#include "qt/stack/varStack/base/baseStack.h"
#include "qt/tools/tools.h"
#include "qt/type/baseType/intTypeObject.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );

	auto varStack = IVarStack::getInstance< BaseStack >( );
	auto typeObject = varStack->generateVar( "int" );
	auto qobjectCast = qobject_cast< IntTypeObject * >( typeObject.get( ) );
	if( qobjectCast )
		*qobjectCast = 122;
	tools::debug::printError( typeObject->toString( ) );
	auto pairs = varStack->permissionVarType( );
	for( auto &element : pairs )
		qDebug( ) << element.first << " : " << element.second;
	return app.exec( );
}
