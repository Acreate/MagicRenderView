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
		tools::debug::printError( "无法创建 " + typeName + " 节点" );
	else {
		qDebug( ) << "节点 " << generateNode->objectName( ) << " 退出";
		generateNode->deleteLater( );
	}
	typeName = "文件信息节点";
	generateNode = nodeStack->generateNode( typeName, mainwidget );
	if( !generateNode )
		tools::debug::printError( "无法创建 " + typeName + " 窗口" );
	else {
		qDebug( ) << "节点 " << generateNode->objectName( ) << " 退出";
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
/// @brief 测试序列化
void checkSerializeVar( ) {
	qDebug( ) << "==================";
	qDebug( ) << "\t\t测试 " << tools::debug::getFunctionName( );
	const auto varStack = IVarStack::getInstance< BaseVarStackEx >( );

#define testSerVar( type_ , old_var_, new_var_) do{ \
		auto typeObject = varStack->generateTUBVar< type_ >( );\
		if( typeObject ) {\
			*typeObject = old_var_;\
			std_vector< uchar > ser;\
			if( typeObject->serializeToVectorData( &ser ) ) {\
				qDebug( ) << __LINE__ << " :("#type_") " << typeObject->toString( );\
				*typeObject = new_var_;\
				qDebug( ) << __LINE__ << " :("#type_") " << typeObject->toString( );\
				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )\
					qDebug( ) << __LINE__ << " :("#type_") " << typeObject->toString( );\
				else\
					tools::debug::printError( " :("#type_") "" 反序列化失败" );\
			} else\
				tools::debug::printError( " :("#type_") "" 序列化失败" );\
		}\
	}while(false)

	testSerVar( IntTypeObject, 11, 33 );
	qDebug( ) << "-------------------";
	testSerVar( FloatTypeObject, 2.44, 57487 );
	qDebug( ) << "-------------------";
	do {
		auto typeObject = varStack->generateTUBVar< StringTypeObject >( );
		if( typeObject ) {
			typeObject->setString( "旧的变量" );
			std_vector< uchar > ser;
			if( typeObject->serializeToVectorData( &ser ) ) {
				qDebug( ) << __LINE__ << " :(""StringTypeObject"") " << typeObject->toString( );
				typeObject->setString( "新的变量" );
				qDebug( ) << __LINE__ << " :(""StringTypeObject"") " << typeObject->toString( );
				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )
					qDebug( ) << __LINE__ << " :(""StringTypeObject"") " << typeObject->toString( );
				else tools::debug::printError( " :(""StringTypeObject"") "" 反序列化失败" );
			} else tools::debug::printError( " :(""StringTypeObject"") "" 序列化失败" );
		}
	} while( false );

	qDebug( ) << "-------------------";
	do {
		auto typeObject = varStack->generateTUBVar< DataTypeObject >( );
		if( typeObject ) {
			typeObject->append( 52 );
			std_vector< uchar > ser;
			if( typeObject->serializeToVectorData( &ser ) ) {
				qDebug( ) << __LINE__ << " :(""DataTypeObject"") " << typeObject->toString( );
			typeObject->append( 8888 );
				qDebug( ) << __LINE__ << " :(""DataTypeObject"") " << typeObject->toString( );
				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )
					qDebug( ) << __LINE__ << " :(""DataTypeObject"") " << typeObject->toString( );
				else tools::debug::printError( " :(""DataTypeObject"") "" 反序列化失败" );
			} else tools::debug::printError( " :(""DataTypeObject"") "" 序列化失败" );
		}
	} while( false );
	qDebug( ) << "\t\t结束 " << tools::debug::getFunctionName( );
	qDebug( ) << "==================";
}
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );

	checkVarStack( &mainwidget );
	checkNodeStack( &mainwidget );
	checkFunction( );
	checkTools( );
	checkSerializeVar( );
	return app.exec( );
}
