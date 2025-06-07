#include "qt/application/application.h"
#include "qt/mainWindow/mainWindow.h"
#include "qt/stack/varStack/base/baseStack.h"
#include "qt/stack/varStack/base/baseStackEx.h"
#include "qt/tools/tools.h"
#include "qt/type/baseType/intTypeObject.h"
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );

	const auto varStack = IVarStack::getInstance< BaseStackEx >( );
	auto typeObject = varStack->generateVar( "int" );
	auto qobjectCast = qobject_cast< IntTypeObject * >( typeObject.get( ) );
	if( qobjectCast )
		*qobjectCast = 122;
	qDebug( ) << typeObject->toString( );
	auto pairs = varStack->permissionVarType( );
	for( auto &element : pairs )
		qDebug( ) << element.first << " : " << element.second;

	auto intTypeObject = varStack->generateTUBVar< IntTypeObject >( );
	if( qobjectCast )
		*qobjectCast = 23;
	qDebug( ) << typeObject->toString( );
	IVarStack::deleteInstance< BaseStackEx >( );
	return app.exec( );
}
