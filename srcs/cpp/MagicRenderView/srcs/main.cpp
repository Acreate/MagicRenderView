#include "qt/application/application.h"
#include "qt/mainWindow/mainWindow.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/tools/tools.h"
#include "qt/type/baseType/floatTypeObject.h"
#include "qt/type/baseType/intTypeObject.h"

/// @brief 检测到堆栈变量的生成
/// @param mainwidget 可能挂靠的父节点
void checkStack( MainWindow &mainwidget ) {
	const auto varStack = IVarStack::getInstance< BaseVarStackEx >( );
	auto typeObject = varStack->generateVar( "int" );
	auto qobjectCast = qobject_cast< IntTypeObject * >( typeObject.get( ) );
	if( qobjectCast )
		*qobjectCast = 122;
	qDebug( ) << typeObject->toString( );
	auto pairs = varStack->permissionVarType( );
	for( auto &element : pairs ) {
		qDebug( ) << element.first << " : " << element.second;
		typeObject = varStack->generateVar( element.first );
		qDebug( ) << typeObject->typeNames( );
	}
	qDebug( ) << "=====================";
	for( auto &element : pairs ) {
		typeObject = varStack->generateVar( element.first );
		qDebug( ) << typeObject->typeNames( );
	}
	qDebug( ) << "=====================";

	auto intTypeObject = varStack->generateTUBVar< IntTypeObject >( );
	if( intTypeObject )
		*intTypeObject = 23;
	qDebug( ) << intTypeObject->toString( );

	auto floatTypeObject = varStack->generateTUBVar< FloatTypeObject >( &mainwidget );
	if( floatTypeObject )
		*floatTypeObject = 123.5;
	qDebug( ) << floatTypeObject->toString( );
	qDebug( ) << floatTypeObject->typeNames( );
	auto generateUbVar = varStack->generateUbVar( "int", &mainwidget );
	IntTypeObject *object;
	object = qobject_cast< IntTypeObject * >( generateUbVar );
	if( object ) {
		*object = 44;
		qDebug( ) << object->toString( );
		qDebug( ) << object->typeNames( );
	}

	static const char cpp17Super[ ] = "int"; // no linkage
	generateUbVar = varStack->generateTUBVar< cpp17Super >( &mainwidget );
	object = qobject_cast< IntTypeObject * >( generateUbVar );
	if( object ) {
		*object = 123.5;
		qDebug( ) << object->toString( );
		qDebug( ) << object->typeNames( );
	}

	auto stdSharedPtr = varStack->generateVar( "file" );
	if( stdSharedPtr ) {
		qDebug( ) << stdSharedPtr->toString( );
		qDebug( ) << stdSharedPtr->typeNames( );
	} else
		tools::debug::printError( "创建失败" );
	IVarStack::deleteInstance< BaseVarStackEx >( );
}
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );

	checkStack( mainwidget );

	return app.exec( );
}
