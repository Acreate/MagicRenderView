#include <stacktrace>

#include "qt/application/application.h"
#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"
#include "qt/mainWindow/mainWindow.h"
#include "qt/stack/nodeStack/INodeStack.h"
#include "qt/stack/nodeStack/base/baseNodeStack.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/tools/tools.h"
#include "qt/type/baseType/dataTypeObject.h"
#include "qt/type/baseType/floatTypeObject.h"
#include "qt/type/baseType/intTypeObject.h"
#include "qt/type/baseType/stringTypeObject.h"
#include "qt/type/blendType/combinationTypeObject.h"
#include "qt/type/lineType/vectorTypeObject.h"

/// @brief 检测到堆栈变量的生成
/// @param mainwidget 可能挂靠的父节点
void checkVarStack( QWidget *mainwidget ) {
	qDebug( ) << "==================";
	qDebug( ) << "\t\t测试 checkVarStack";
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

	auto floatTypeObject = varStack->generateTUBVar< FloatTypeObject >( mainwidget );
	if( floatTypeObject )
		*floatTypeObject = 123.5;
	qDebug( ) << floatTypeObject->toString( );
	qDebug( ) << floatTypeObject->typeNames( );
	auto generateUbVar = varStack->generateUbVar( "int", mainwidget );
	IntTypeObject *object;
	object = qobject_cast< IntTypeObject * >( generateUbVar );
	if( object ) {
		*object = 44;
		qDebug( ) << object->toString( );
		qDebug( ) << object->typeNames( );
	}

	static const char cpp17Super[ ] = "int"; // no linkage
	generateUbVar = varStack->generateTUBVar< cpp17Super >( mainwidget );
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

	if( stdSharedPtr != nullptr )
		qDebug( ) << "不等于 nullptr";

	if( *stdSharedPtr != nullptr )
		qDebug( ) << "不等于 nullptr";
	IVarStack::deleteInstance< BaseVarStackEx >( );

	qDebug( ) << "\n\n" << "开始测试 \"(iTypeObject *)nullptr\" 转换";

#define TestConverPtr(type_) \
		do {\
		type_ *nnu = nullptr;\
		type_ nullptrConverObj = ( type_ ) ( *nnu );\
		if( nullptrConverObj != nullptr )\
			qDebug( ) << "\"("<< #type_ <<" *)nullptr\" 不等于 nullptr";\
		else\
			qDebug( ) << "\"("<< #type_ <<" *)nullptr\" 等于 nullptr";\
		}while(false)

	TestConverPtr( IntTypeObject );
	TestConverPtr( FloatTypeObject );
	TestConverPtr( DataTypeObject );
	TestConverPtr( NullTypeObject );
	TestConverPtr( StringTypeObject );
	TestConverPtr( CombinationTypeObject );
	TestConverPtr( VectorTypeObject );
	TestConverPtr( PairtTypeObject );

	qDebug( ) << "\n\n" << "开始测试 \"(iTypeObject *)nullptr\" 转换";
#define TestConverITypeObjectPtr(type_) \
		do {\
		ITypeObject *nnu = nullptr;\
		type_ nullptrConverObj = *nnu;\
		if( nullptrConverObj != nullptr )\
			qDebug( ) << "\"("<< #type_ <<" *)nullptr\" 不等于 nullptr";\
		else\
			qDebug( ) << "\"("<< #type_ <<" *)nullptr\" 等于 nullptr";\
		}while(false)

	TestConverITypeObjectPtr( IntTypeObject );
	TestConverITypeObjectPtr( FloatTypeObject );
	TestConverITypeObjectPtr( DataTypeObject );
	TestConverITypeObjectPtr( NullTypeObject );
	TestConverITypeObjectPtr( StringTypeObject );
	TestConverITypeObjectPtr( CombinationTypeObject );
	TestConverITypeObjectPtr( VectorTypeObject );
	TestConverITypeObjectPtr( PairtTypeObject );

	qDebug( ) << "\n\n" << "开始测试 \"(iTypeObject *)nullptr\" 转换-多层赋值";
#define TestConverMulEquPtr(type_) \
		do {\
		type_ *nnu = nullptr;\
		type_ nullptrConverObj = ( type_ ) ( *nnu );\
		type_ nullptrConverObj2 = nullptrConverObj;\
		if( nullptrConverObj2 != nullptr )\
			qDebug( ) << "\"("<< #type_ <<" *)nullptr\" 不等于 nullptr";\
		else\
			qDebug( ) << "\"("<< #type_ <<" *)nullptr\" 等于 nullptr";\
		}while(false)

	TestConverMulEquPtr( IntTypeObject );
	TestConverMulEquPtr( FloatTypeObject );
	TestConverMulEquPtr( DataTypeObject );
	TestConverMulEquPtr( NullTypeObject );
	TestConverMulEquPtr( StringTypeObject );
	TestConverMulEquPtr( CombinationTypeObject );
	TestConverMulEquPtr( VectorTypeObject );
	TestConverMulEquPtr( PairtTypeObject );

	qDebug( ) << "\t\t结束 checkVarStack";
	qDebug( ) << "==================\n";
}
void checkNodeStack( QWidget *mainwidget ) {
	qDebug( ) << "==================";
	qDebug( ) << "\t\t测试 checkNodeStack";
	qDebug( ) << "===";
	auto nodeStack = INodeStack::getInstance< BaseNodeStack >( );
	auto propertyNames = nodeStack->permissionNodeType( );
	for( auto &name : propertyNames )
		qDebug( ) << name.first;
	qDebug( ) << "===";
	QString typeName = "fileInfo";
	auto generateNode = nodeStack->generateNode( typeName, mainwidget );
	if( !generateNode )
		tools::debug::printError( "无法创建 " + typeName + " 窗口" );
	else {
		qDebug( ) << "窗口 " << generateNode->objectName( ) << " 退出";
		generateNode->deleteLater( );
	}
	qDebug( ) << "\t\t结束 checkNodeStack";
	qDebug( ) << "==================\n";
}
/// @brief 测试函数
void checkFunction( ) {
	qDebug( ) << "==========================";
	auto userFunctionDeclaration = UserFunctionDeclaration(
		"file fileInfo(string); ",
		[]( ) {
		} );
	qDebug( ) << userFunctionDeclaration.getReturnType( );
	qDebug( ) << userFunctionDeclaration.getDeclarationName( );
	for( auto &ptr : userFunctionDeclaration.getParamInfos( ) )
		qDebug( ) << ptr->first << " : " << ptr->second;
	qDebug( ) << "==========================";
}
/// @brief 测试工具函数
void checkTools( ) {
	qDebug( ) << "==========================";
	std_vector< std_pairt< QString, size_t > > functionName;
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( 1 );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( 0, 1 );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( functionName );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( 1, functionName );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( 0, 1, functionName );
	qDebug( ) << "==========================";
}
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );

	checkVarStack( &mainwidget );
	checkNodeStack( &mainwidget );
	checkFunction( );
	checkTools( );
	return app.exec( );
}
