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
#include "qt/type/baseType/nullTypeObject.h"
#include "qt/type/baseType/stringTypeObject.h"
#include "qt/type/blendType/combinationTypeObject.h"
#include "qt/type/lineType/vectorTypeObject.h"
#include "qt/type/sequenceType/pairtTypeObject.h"

#if _DEBUG
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
	qDebug( ) << __LINE__ << " : " << typeObject->toString( );
	auto pairs = varStack->permissionVarType( );
	for( auto &element : pairs ) {
		qDebug( ) << __LINE__ << " : " << element.first << " : " << element.second;
		typeObject = varStack->generateVar( element.first );
		qDebug( ) << __LINE__ << " : " << typeObject->typeNames( );
	}
	qDebug( ) << "=====================";
	for( auto &element : pairs ) {
		typeObject = varStack->generateVar( element.first );
		qDebug( ) << __LINE__ << " : " << typeObject->typeNames( );
	}
	qDebug( ) << "=====================";

	auto intTypeObject = varStack->generateTUBVar< IntTypeObject >( );
	if( intTypeObject )
		*intTypeObject = 23;
	qDebug( ) << __LINE__ << " : " << intTypeObject->toString( );

	auto floatTypeObject = varStack->generateTUBVar< FloatTypeObject >( mainwidget );
	if( floatTypeObject )
		*floatTypeObject = 123.5;
	qDebug( ) << __LINE__ << " : " << floatTypeObject->toString( );
	qDebug( ) << __LINE__ << " : " << floatTypeObject->typeNames( );
	auto generateUbVar = varStack->generateUbVar( "int", mainwidget );
	IntTypeObject *object;
	object = qobject_cast< IntTypeObject * >( generateUbVar );
	if( object ) {
		*object = 44;
		qDebug( ) << __LINE__ << " : " << object->toString( );
		qDebug( ) << __LINE__ << " : " << object->typeNames( );
	}

	static const char cpp17Super[ ] = "int"; // no linkage
	generateUbVar = varStack->generateTUBVar< cpp17Super >( mainwidget );
	object = qobject_cast< IntTypeObject * >( generateUbVar );
	if( object ) {
		*object = 123.5;
		qDebug( ) << __LINE__ << " : " << object->toString( );
		qDebug( ) << __LINE__ << " : " << object->typeNames( );
	}

	auto stdSharedPtr = varStack->generateVar( "file" );
	if( stdSharedPtr ) {
		qDebug( ) << __LINE__ << " : " << stdSharedPtr->toString( );
		qDebug( ) << __LINE__ << " : " << stdSharedPtr->typeNames( );
	} else
		tools::debug::printError( "创建失败" );

	if( stdSharedPtr != nullptr )
		qDebug( ) << __LINE__ << " : " << "不等于 nullptr";

	if( *stdSharedPtr != nullptr )
		qDebug( ) << __LINE__ << " : " << "不等于 nullptr";
	IVarStack::deleteInstance< BaseVarStackEx >( );

	qDebug( ) << "\n\n" << "开始测试 \"(iTypeObject *)nullptr\" 转换";

#define TestConverPtr(type_) \
		do {\
		type_ *nnu = nullptr;\
		type_ nullptrConverObj = ( type_ ) ( *nnu );\
		if( nullptrConverObj != nullptr )\
			qDebug( ) << __LINE__ << " : " << "\"("<< #type_ <<" *)nullptr\" 不等于 nullptr";\
		else\
			qDebug( ) << __LINE__ << " : " << "\"("<< #type_ <<" *)nullptr\" 等于 nullptr";\
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
			qDebug( ) << __LINE__ << " : "  << "\"("<< #type_ <<" *)nullptr\" 不等于 nullptr";\
		else\
			qDebug( ) << __LINE__ << " : "  << "\"("<< #type_ <<" *)nullptr\" 等于 nullptr";\
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
			qDebug( ) << __LINE__ << " : "  << "\"("<< #type_ <<" *)nullptr\" 不等于 nullptr";\
		else\
			qDebug( ) << __LINE__ << " : "  << "\"("<< #type_ <<" *)nullptr\" 等于 nullptr";\
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
		qDebug( ) << __LINE__ << " : " << name.first;
	qDebug( ) << "===";
	QString typeName = "fileInfo";
	auto generateNode = nodeStack->generateNode( typeName, mainwidget );
	if( !generateNode )
		tools::debug::printError( "无法创建 " + typeName + " 节点" );
	else {
		qDebug( ) << __LINE__ << " : " << "节点 " << generateNode->objectName( ) << " 退出";
		generateNode->deleteLater( );
	}
	typeName = "文件信息节点";
	generateNode = nodeStack->generateNode( typeName, mainwidget );
	if( !generateNode )
		tools::debug::printError( "无法创建 " + typeName + " 窗口" );
	else {
		qDebug( ) << __LINE__ << " : " << "节点 " << generateNode->objectName( ) << " 退出";
		generateNode->deleteLater( );
	}
	qDebug( ) << "\t\t结束 checkNodeStack";
	qDebug( ) << "==================\n";
}
/// @brief 测试函数
void checkFunction( ) {
	qDebug( ) << "==========================";
	auto userFunctionDeclaration = UserFunctionDeclaration(
		"file fileInfo(string,string); ",
		[]( ) {
		} );
	qDebug( ) << __LINE__ << " : " << userFunctionDeclaration.getReturnType( );
	qDebug( ) << __LINE__ << " : " << userFunctionDeclaration.getDeclarationName( );
	for( auto &ptr : userFunctionDeclaration.getParamInfos( ) )
		qDebug( ) << __LINE__ << " : " << ptr->first << " : " << ptr->second;
	qDebug( ) << "==========================";
}
/// @brief 测试工具函数
void checkTools( ) {
	qDebug( ) << "\n==========================";
	std_vector< std_pairt< QString, size_t > > functionName;
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( 1 );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( 0, 1 );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( functionName );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( 1, functionName );
	qDebug( ) << __LINE__ << " : " << tools::debug::getFunctionName( 0, 1, functionName );
	qDebug( ) << "\n==========================";
}
/// @brief 测试序列化
void checkSerializeVar( ) {
	qDebug( ) << "\n==================";
	qDebug( ) << "\t\t测试 " << tools::debug::getFunctionName( ) << "\n\n";
	const auto varStack = IVarStack::getInstance< BaseVarStackEx >( );

#define testSerVar( type_ , old_var_, new_var_) do{ \
		auto typeObject = varStack->generateTVar< type_ >( );\
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
		auto typeObject = varStack->generateTVar< NullTypeObject >( );
		if( typeObject ) {
			std_vector< uchar > ser;
			if( typeObject->serializeToVectorData( &ser ) ) {
				qDebug( ) << __LINE__ << " :(""NullTypeObject"") " << typeObject->toString( );
				qDebug( ) << __LINE__ << " :(""NullTypeObject"") " << typeObject->toString( );
				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )
					qDebug( ) << __LINE__ << " :(""NullTypeObject"") " << typeObject->toString( );
				else tools::debug::printError( " :(""NullTypeObject"") "" 反序列化失败" );
			} else tools::debug::printError( " :(""NullTypeObject"") "" 序列化失败" );
		}
	} while( false );

	qDebug( ) << "-------------------";
	do {
		auto typeObject = varStack->generateTVar< VectorTypeObject >( );
		if( typeObject ) {
			auto unity1 = varStack->generateTVar< IntTypeObject >( );
			*unity1 = 22;
			auto unity2 = varStack->generateTVar< FloatTypeObject >( );
			*unity2 = 99.5;
			typeObject->append( unity1 );
			typeObject->append( unity2 );
			std_vector< uchar > ser;
			if( typeObject->serializeToVectorData( &ser ) ) {
				qDebug( ) << __LINE__ << " :(""VectorTypeObject"") " << typeObject->toString( );
				*unity1 = 100;
				*unity2 = 55555.2;
				qDebug( ) << __LINE__ << " :(""VectorTypeObject"") " << typeObject->toString( );
				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )
					qDebug( ) << __LINE__ << " :(""VectorTypeObject"") " << typeObject->toString( );
				else tools::debug::printError( " :(""VectorTypeObject"") "" 反序列化失败" );
			} else
				tools::debug::printError( " :(""VectorTypeObject"") "" 序列化失败" );
		}
	} while( false );
	qDebug( ) << "-------------------";
	do {
		auto typeObject = varStack->generateTVar< StringTypeObject >( );
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
		auto typeObject = varStack->generateTVar< DataTypeObject >( );
		if( typeObject ) {
			typeObject->append( 52 );
			std_vector< uchar > ser;
			if( typeObject->serializeToVectorData( &ser ) ) {
				qDebug( ) << __LINE__ << " :(""DataTypeObject"") " << typeObject->toString( );
				typeObject->clear( );
				typeObject->append( 8888 );
				typeObject->append( 45 );
				typeObject->append( 1112 );
				qDebug( ) << __LINE__ << " :(""DataTypeObject"") " << typeObject->toString( );
				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )
					qDebug( ) << __LINE__ << " :(""DataTypeObject"") " << typeObject->toString( );
				else tools::debug::printError( " :(""DataTypeObject"") "" 反序列化失败" );
			} else tools::debug::printError( " :(""DataTypeObject"") "" 序列化失败" );
		}
	} while( false );

	qDebug( ) << "-------------------";
	do {
		auto typeObject = varStack->generateTVar< IntTypeObject >( );
		if( typeObject ) {
			*typeObject = 12;
			std_vector< uchar > ser;
			if( typeObject->serializeToVectorData( &ser ) ) {
				qDebug( ) << __LINE__ << " :(""IntTypeObject"") " << typeObject->toString( );
				*typeObject = 32;
				qDebug( ) << __LINE__ << " :(""IntTypeObject"") " << typeObject->toString( );

				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )
					qDebug( ) << __LINE__ << " :(""IntTypeObject"") " << typeObject->toString( );
				else tools::debug::printError( " :(""IntTypeObject"") "" 反序列化失败" );
				qDebug( ) << __LINE__ << " : " << "开始测试 ISerialize::SerializeInfo 功能";
				ISerialize::SerializeInfo info( ser.data( ), ser.size( ) );
				if( info.init( ) ) {
					QStringList list;
					for( auto &typeName : info.getStackNames( ) )
						list.append( typeName );
					qDebug( ) << __LINE__ << " : " << "堆栈列表 : " << list.join( ", " );
					list.clear( );
					for( auto &typeName : info.getTypeNames( ) )
						list.append( typeName );
					qDebug( ) << __LINE__ << " : " << "类型列表 : " << list.join( ", " );
					list.clear( );
					for( auto &typeName : info.getMetaObjectClassNames( ) )
						list.append( typeName );
					qDebug( ) << __LINE__ << " : " << "多媒体列表 : " << list.join( ", " );

					auto typeNames = info.getTypeNames( );
					QString string = typeNames[ typeNames.size( ) - 1 ];
					auto var = varStack->generateVar( string );
					if( var ) {
						qDebug( ) << __LINE__ << " : " << "创建成功 : " << var->typeNames( );
						qDebug( ) << __LINE__ << " : " << var->toString( );
					}
				} else
					tools::debug::printError( "ISerialize::SerializeInfo 功能缺陷" );
			} else
				tools::debug::printError( " :(""IntTypeObject"") "" 序列化失败" );
		}
	} while( false );

	qDebug( ) << "\n\t\t结束 " << tools::debug::getFunctionName( );
	qDebug( ) << "==================";
}
#endif
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

	MainWindow mainwidget;
	mainwidget.show( );
#if _DEBUG
	checkVarStack( &mainwidget );
	checkNodeStack( &mainwidget );
	checkFunction( );
	checkTools( );
	checkSerializeVar( );
#endif
	return app.exec( );
}
