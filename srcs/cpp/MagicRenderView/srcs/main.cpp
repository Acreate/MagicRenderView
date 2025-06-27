#include "qt/application/application.h"
#include "qt/mainWindow/mainWindow.h"

#if _DEBUG

#include <stacktrace>
#include "qt/tools/tools.h"
#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"
#include "qt/stack/nodeStack/base/baseNodeStack.h"
#include "qt/stack/varStack/base/baseVarStackEx.h"
#include "qt/type/baseType/dataTypeObject.h"
#include "qt/type/baseType/floatTypeObject.h"
#include "qt/type/baseType/intTypeObject.h"
#include "qt/type/baseType/nullTypeObject.h"
#include "qt/type/baseType/stringTypeObject.h"
#include "qt/type/blendType/combinationTypeObject.h"
#include "qt/type/lineType/vectorTypeObject.h"
#include "qt/type/sequenceType/pairtTypeObject.h"
#include "qt/stack/nodeStack/INodeStack.h"

/// @brief 检测到堆栈变量的生成
void checkVarStack( ) {
	qDebug( ) << "==================";
	qDebug( ) << "\t\t测试 checkVarStack";
	auto varStack = IVarStack::getInstance< BaseVarStackEx >( );
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

	auto floatTypeObject = varStack->generateTUBVar< FloatTypeObject >( );
	if( floatTypeObject )
		*floatTypeObject = 123.5;
	qDebug( ) << __LINE__ << " : " << floatTypeObject->toString( );
	qDebug( ) << __LINE__ << " : " << floatTypeObject->typeNames( );
	auto generateUbVar = varStack->generateUbVar( "int" );
	IntTypeObject *object;
	object = qobject_cast< IntTypeObject * >( generateUbVar );
	if( object ) {
		*object = 44;
		qDebug( ) << __LINE__ << " : " << object->toString( );
		qDebug( ) << __LINE__ << " : " << object->typeNames( );
	}

	static const char cpp17Super[ ] = "int"; // no linkage
	generateUbVar = varStack->generateTUBVar< cpp17Super >( );
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
void checkNodeStack( ) {
	qDebug( ) << "==================";
	qDebug( ) << "\t\t测试 checkNodeStack";
	qDebug( ) << "===";
	auto nodeStack = INodeStack::getInstance< BaseNodeStack >( );
	auto propertyNames = nodeStack->permissionNodeType( );
	for( auto &name : propertyNames )
		qDebug( ) << __LINE__ << " : " << name.first;
	qDebug( ) << "===";
	QString typeName = "fileInfo";
	auto generateNode = nodeStack->generateNode( typeName );
	if( !generateNode )
		tools::debug::printError( "无法创建 " + typeName + " 节点" );
	else {
		qDebug( ) << __LINE__ << " : " << "节点 " << generateNode->objectName( ) << " 退出";
		generateNode->deleteLater( );
	}
	typeName = "文件信息节点";
	generateNode = nodeStack->generateNode( typeName );
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
	if( Application::getApplicationInstancePtr( ) )
		qDebug( ) << __LINE__ << " : " << "获取实例指针成功";
	else
		qDebug( ) << __LINE__ << " : " << "获取实例指针失败";

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
	auto varStack = IVarStack::getInstance< BaseVarStackEx >( );

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
			} \
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
			}
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
			}
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
			}
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
				}
			}
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
			}
		}
	} while( false );
	qDebug( ) << "-------------------";
	do {
		auto typeObject = varStack->generateTVar< PairtTypeObject >( );
		if( typeObject ) {
			auto unity1 = varStack->generateTVar< StringTypeObject >( );
			*unity1 = "first";
			auto unity2 = varStack->generateTVar< StringTypeObject >( );
			*unity2 = "scond";
			typeObject->setFirst( unity1 );
			typeObject->setScond( unity2 );
			std_vector< uchar > ser;
			if( typeObject->serializeToVectorData( &ser ) ) {
				qDebug( ) << __LINE__ << " :(""PairtTypeObject"") " << typeObject->toString( );
				*unity1 = "0x100-1";
				*unity2 = "0x55555.2+5";
				qDebug( ) << __LINE__ << " :(""PairtTypeObject"") " << typeObject->toString( );
				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )
					qDebug( ) << __LINE__ << " :(""PairtTypeObject"") " << typeObject->toString( );
			}
		}
	} while( false );
	qDebug( ) << "-------------------";
	do {
		auto typeObject = varStack->generateTVar< CombinationTypeObject >( );
		if( typeObject ) {
			auto unity1 = varStack->generateTVar< StringTypeObject >( );
			*unity1 = "first";
			auto unity2 = varStack->generateTVar< StringTypeObject >( );
			*unity2 = "scond";
			auto unity3 = varStack->generateTVar< IntTypeObject >( );
			auto unity4 = varStack->generateTVar< FloatTypeObject >( );
			*unity3 = 23;
			*unity4 = 99.2201;
			typeObject->setVarObject( unity1, "1" );
			typeObject->setVarObject( unity2, "2" );
			typeObject->setVarObject( unity3, "5" );
			typeObject->setVarObject( unity4, "unity4" );
			std_vector< uchar > ser;
			if( typeObject->serializeToVectorData( &ser ) ) {
				qDebug( ) << __LINE__ << " :(""CombinationTypeObject"") " << typeObject->toString( );
				*unity1 = "100";
				*unity2 = "55555.2";
				*unity3 = 0;
				*unity4 = 1;
				qDebug( ) << __LINE__ << " :(""CombinationTypeObject"") " << typeObject->toString( );
				if( typeObject->serializeToObjectData( ser.data( ), ser.size( ) ) )
					qDebug( ) << __LINE__ << " :(""CombinationTypeObject"") " << typeObject->toString( );
			}
		}
	} while( false );
	qDebug( ) << "-------------------";
	qDebug( ) << "\n\t\t结束 " << tools::debug::getFunctionName( );
	qDebug( ) << "==================";
}

#endif
int main( int argc, char *argv[ ] ) {
	Application app( argc, argv );

#if _DEBUG
	checkVarStack( );
	checkNodeStack( );
	checkFunction( );
	checkTools( );
	checkSerializeVar( );
#endif

	MainWindow mainwidget;
	mainwidget.show( );

	return app.exec( );
}
