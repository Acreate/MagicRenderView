#include "testCodeSources.h"
#include <QDebug>
#include <qfileinfo.h>
#include <QMetaEnum>
#include <QStandardPaths>

#include "../app/application.h"

#include "../director/iniDirector.h"
#include "../director/printerDirector.h"
#include "../director/varDirector.h"

#include "../enums/nodeEnum.h"

#include "../srack/srackInfo.h"
#include "../tools/arrayTools.h"
#include "../tools/enumTools.h"

#include "../tools/pathTools.h"

template< typename TTestType >
void testVarGener( const TTestType &default_var ) {
	auto name = typeid( TTestType ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varDirector = instancePtr->getVarDirector( );
	TTestType *checkVar;
	if( varDirector->create< TTestType >( checkVar ) ) {
		*checkVar = default_var;
		std::vector< uint8_t > buff;
		uint64_t count;
		if( varDirector->toVector( checkVar, buff ) ) {
			qDebug( ) << QObject::tr( "序列化值:" ).toStdString( ).c_str( ) << *checkVar;
			void *converPtr = nullptr;
			if( varDirector->toVar( count, buff.data( ), buff.size( ), converPtr ) ) {
				TTestType *castPtr;
				varDirector->cast_ptr< TTestType >( converPtr, castPtr );
				qDebug( ) << QObject::tr( "反序列化:" ).toStdString( ).c_str( ) << *castPtr;
			} else
				instancePtr->getPrinterDirector( )->error( QObject::tr( "反序列哈失败" ) + name, Create_SrackInfo( ) );
		} else
			instancePtr->getPrinterDirector( )->error( QObject::tr( "序列化失败 " ) + name, Create_SrackInfo( ) );
	} else
		instancePtr->getPrinterDirector( )->error( QObject::tr( "创建失败 " ) + name, Create_SrackInfo( ) );
	qDebug( ) << "";
}

template< typename TTestFirstType, typename TTestScondType >
void testPairVarGener( const TTestFirstType &first_var_value, const TTestScondType &scond_var_varlue ) {
	auto name = typeid( std::pair< void *, void * > ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varDirector = instancePtr->getVarDirector( );
	std::pair< void *, void * > *checkVar;
	if( varDirector->create< std::pair< void *, void * > >( checkVar ) ) {
		TTestFirstType *first;
		varDirector->create< TTestFirstType >( first );
		TTestScondType *scond;
		varDirector->create< TTestScondType >( scond );
		*first = first_var_value;
		*scond = scond_var_varlue;
		checkVar->first = first;
		checkVar->second = scond;
		std::vector< uint8_t > buff;
		uint64_t count;
		if( varDirector->toVector( checkVar, buff ) ) {
			qDebug( ) << QObject::tr( "序列化值:" ).toStdString( ).c_str( ) << *first << ", " << *scond;
			void *converPtr = nullptr;
			if( varDirector->toVar( count, buff.data( ), buff.size( ), converPtr ) ) {
				std::pair< void *, void * > *castPtr;
				varDirector->cast_ptr< std::pair< void *, void * > >( converPtr, castPtr );
				varDirector->cast_ptr< int32_t >( castPtr->first, first );
				varDirector->cast_ptr< QString >( castPtr->second, scond );
				qDebug( ) << QObject::tr( "反序列化:" ).toStdString( ).c_str( ) << *first << ", " << *scond;
			} else
				instancePtr->getPrinterDirector( )->error( QObject::tr( "反序列哈失败 " ) + name, Create_SrackInfo( ) );
		} else
			instancePtr->getPrinterDirector( )->error( QObject::tr( "序列化失败 " ) + name, Create_SrackInfo( ) );
	} else
		instancePtr->getPrinterDirector( )->error( QObject::tr( "创建失败 " ) + name, Create_SrackInfo( ) );
	qDebug( ) << "";
}

template< typename TTestFirstType >
void testArrayVarGener( const TTestFirstType &first_var_value, const size_t &array_count ) {
	auto name = typeid( std::vector< TTestFirstType > ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varDirector = instancePtr->getVarDirector( );
	std::vector< TTestFirstType > *checkVar;
	if( varDirector->create< std::vector< TTestFirstType > >( checkVar ) ) {
		checkVar->resize( array_count, first_var_value );
		std::vector< uint8_t > buff;
		uint64_t count;
		if( varDirector->toVector( checkVar, buff ) ) {
			QStringList data;
			auto arrayDataPtr = checkVar->data( );
			for( size_t index = 0; index < array_count; ++index )
				data.append( QString( "%1" ).arg( arrayDataPtr[ index ] ) );
			qDebug( ) << QObject::tr( "序列化值:" ).toStdString( ).c_str( ) << data.join( ", " ).toStdString( ).c_str( );
			void *converPtr = nullptr;
			if( varDirector->toVar( count, buff.data( ), buff.size( ), converPtr ) ) {
				data.clear( );
				std::vector< TTestFirstType > *castPtr;
				varDirector->cast_ptr< std::vector< TTestFirstType > >( converPtr, castPtr );
				auto arratCount = castPtr->size( );
				if( arratCount == array_count ) {
					arrayDataPtr = castPtr->data( );
					for( size_t index = 0; index < array_count; ++index )
						data.append( QString( "%1" ).arg( arrayDataPtr[ index ] ) );
					qDebug( ) << QObject::tr( "反序列化:" ).toStdString( ).c_str( ) << data.join( ", " ).toStdString( ).c_str( );
				} else
					instancePtr->getPrinterDirector( )->error( QObject::tr( "反序列哈失败[数量不匹配] " ) + name, Create_SrackInfo( ) );
			} else
				instancePtr->getPrinterDirector( )->error( QObject::tr( "反序列哈失败 " ) + name, Create_SrackInfo( ) );
		} else
			instancePtr->getPrinterDirector( )->error( QObject::tr( "序列化失败 " ) + name, Create_SrackInfo( ) );
	} else
		instancePtr->getPrinterDirector( )->error( QObject::tr( "创建失败 " ) + name, Create_SrackInfo( ) );
	qDebug( ) << "";
}

template< typename TTestFirstType >
void testAnyArrayVarGener( const TTestFirstType &first_var_value, const size_t &array_count ) {
	auto name = typeid( std::vector< void * > ).name( );
	qDebug( ) << "";
	qDebug( ) << name;
	auto instancePtr = Application::getInstancePtr( );
	auto varDirector = instancePtr->getVarDirector( );
	std::vector< void * > *checkVar;
	if( varDirector->create< std::vector< void * > >( checkVar ) ) {
		checkVar->resize( array_count, nullptr );
		QStringList data;
		auto arrayDataPtr = checkVar->data( );
		TTestFirstType *unityVar;
		for( size_t index = 0; index < array_count; ++index ) {
			if( varDirector->create< TTestFirstType >( unityVar ) == false ) {
				auto name = typeid( std::vector< void * > ).name( );
				qDebug( ) << QObject::tr( "单元创建失败:" ).toStdString( ).c_str( ) << name;
				return;
			}
			*unityVar = first_var_value;
			arrayDataPtr[ index ] = unityVar;
			data.append( QString( "%1" ).arg( *unityVar ) );
		}
		std::vector< uint8_t > buff;
		uint64_t count;
		if( varDirector->toVector( checkVar, buff ) ) {
			qDebug( ) << QObject::tr( "序列化值:" ).toStdString( ).c_str( ) << data.join( ", " ).toStdString( ).c_str( );
			void *converPtr = nullptr;
			if( varDirector->toVar( count, buff.data( ), buff.size( ), converPtr ) ) {
				data.clear( );
				std::vector< void * > *castPtr;
				varDirector->cast_ptr< std::vector< void * > >( converPtr, castPtr );
				arrayDataPtr = castPtr->data( );
				TTestFirstType *unityVar;
				for( size_t index = 0; index < array_count; ++index ) {
					if( varDirector->cast_ptr< TTestFirstType >( arrayDataPtr[ index ], unityVar ) == false ) {
						auto name = typeid( std::vector< void * > ).name( );
						qDebug( ) << QObject::tr( "单元转换失败:" ).toStdString( ).c_str( ) << name;
						return;
					}
					data.append( QString( "%1" ).arg( *unityVar ) );
				}
				qDebug( ) << QObject::tr( "反序列化:" ).toStdString( ).c_str( ) << data.join( ", " ).toStdString( ).c_str( );
			} else
				instancePtr->getPrinterDirector( )->error( QObject::tr( "反序列哈失败 " ) + name, Create_SrackInfo( ) );
		} else
			instancePtr->getPrinterDirector( )->error( QObject::tr( "序列化失败 " ) + name, Create_SrackInfo( ) );
	} else
		instancePtr->getPrinterDirector( )->error( QObject::tr( "创建失败 " ) + name, Create_SrackInfo( ) );
	qDebug( ) << "";
}

void TestCodeSources::testVarGener( ) {
	::testVarGener< float >( 155.2 );
	::testVarGener< double >( 255.1 );
	::testVarGener< int8_t >( 255.1 );
	::testVarGener< int16_t >( 255.1 );
	::testVarGener< int32_t >( 255.1 );
	::testVarGener< int64_t >( 255.1 );
	::testVarGener< uint8_t >( 255.1 );
	::testVarGener< uint16_t >( -255.1 );
	::testVarGener< uint32_t >( -255.1 );
	::testVarGener< uint64_t >( -255.1 );
	::testVarGener< QString >( "255.1，含糊" );
	::testPairVarGener< int32_t, QString >( 0, "" );
	::testPairVarGener< int32_t, QString >( 888, "323" );
	::testPairVarGener< int32_t, QString >( 888, "323汉文化" );
	::testArrayVarGener< float >( 155.2, 5 );
	::testArrayVarGener< double >( 255.1, 5 );
	::testArrayVarGener< uint8_t >( -547, 5 );
	::testArrayVarGener< uint16_t >( -547, 5 );
	::testArrayVarGener< uint32_t >( -547, 5 );
	::testArrayVarGener< uint64_t >( -547, 5 );
	::testArrayVarGener< int8_t >( 547, 5 );
	::testArrayVarGener< int16_t >( 547, 5 );
	::testArrayVarGener< int32_t >( 547, 5 );
	::testArrayVarGener< int64_t >( 547, 5 );
	::testArrayVarGener< QString >( "547", 5 );
	::testArrayVarGener< QString >( "", 5 );
	::testArrayVarGener< QString >( "985单元", 5 );
	::testAnyArrayVarGener< int64_t >( 999, 5 );
	::testAnyArrayVarGener< QString >( "", 5 );
	::testAnyArrayVarGener< QString >( "985单元", 5 );
}
void TestCodeSources::testAppSaveBin( ) {
	auto instancePtr = Application::getInstancePtr( );
	std::vector< uint8_t > buff = std::vector< uint8_t > { 1, 2, 3, 4 };
	instancePtr->setVar( "第1", buff );
	buff = std::vector< uint8_t > { 15, 16, 17, 18 };
	instancePtr->setVar( "第2", buff );
	QString saveFile = "保存bin.bin";
	instancePtr->synchronousVarToFile( );
	instancePtr->clearVar( );
	instancePtr->synchronousFileToVar( );
}
void TestCodeSources::testEnumConver( ) {
	auto instancePtr = Application::getInstancePtr( );
	auto printerDirector = instancePtr->getPrinterDirector( );
	QString enum_string;
	NodeEnum::ErrorType result_ErrorType_var;
	NodeEnum::AdviseType result_AdviseType_var;
	enum_string = "Other";
	if( EnumTools::converToEnum( enum_string, result_ErrorType_var ) ) {
		printerDirector->info( enum_string, Create_SrackInfo( ) );
	} else
		printerDirector->error( QObject::tr( "字符串转枚举失败 [NodeEnum::ErrorType]" ), Create_SrackInfo( ) );

	enum_string = "Result";
	if( EnumTools::converToEnum( enum_string, result_AdviseType_var ) ) {
		printerDirector->info( enum_string, Create_SrackInfo( ) );
	} else
		printerDirector->error( QObject::tr( "字符串转枚举失败 [NodeEnum::AdviseType]" ), Create_SrackInfo( ) );

	result_ErrorType_var = NodeEnum::ErrorType::Other;
	enum_string.clear( );
	if( EnumTools::converToString( result_ErrorType_var, enum_string ) ) {
		printerDirector->info( enum_string, Create_SrackInfo( ) );
	} else
		printerDirector->error( QObject::tr( "枚举转字符串失败 [NodeEnum::ErrorType]" ), Create_SrackInfo( ) );

	result_AdviseType_var = NodeEnum::AdviseType::Result;
	enum_string.clear( );
	if( EnumTools::converToString( result_AdviseType_var, enum_string ) ) {
		printerDirector->info( enum_string, Create_SrackInfo( ) );
	} else
		printerDirector->error( QObject::tr( "枚举转字符串失败 [NodeEnum::AdviseType]" ), Create_SrackInfo( ) );

}
void TestCodeSources::testAppFile( ) {

	auto instancePtr = Application::getInstancePtr( );
	auto printerDirector = instancePtr->getPrinterDirector( );

	if( pathTools::hasDir( "." ) )
		printerDirector->info( QObject::tr( "存在路径[.]" ), Create_SrackInfo( ) );
	else
		printerDirector->info( QObject::tr( "非法路径[.]" ), Create_SrackInfo( ) );

	if( pathTools::hasFile( "." ) )
		printerDirector->info( QObject::tr( "存在文件[.]" ), Create_SrackInfo( ) );
	else
		printerDirector->info( QObject::tr( "非法文件[.]" ), Create_SrackInfo( ) );
	if( pathTools::createFile( "./45/file" ) )
		printerDirector->info( QObject::tr( "创建文件[./45/file]成功" ), Create_SrackInfo( ) );
	else
		printerDirector->info( QObject::tr( "创建文件[./45/file]失败" ), Create_SrackInfo( ) );
	QFileInfo getPathInfo;
	if( pathTools::getPathHasFileInfo( "./4541/88", getPathInfo ) ) {
		printerDirector->info( QObject::tr( "获取路径[./4541/88]成功" ), Create_SrackInfo( ) );
		if( getPathInfo.isFile( ) )
			printerDirector->info( QObject::tr( "获取路径[%1]是%2" ).arg( getPathInfo.absoluteFilePath( ) ).arg( QObject::tr( "文件" ) ), Create_SrackInfo( ) );
		else
			printerDirector->info( QObject::tr( "获取路径[%1]是%2" ).arg( getPathInfo.absoluteFilePath( ) ).arg( QObject::tr( "目录" ) ), Create_SrackInfo( ) );
	} else
		printerDirector->info( QObject::tr( "获取路径[./4541/88]失败" ), Create_SrackInfo( ) );
	printerDirector->info( pathTools::normalPathSeparatorToPath( "/1/2//3/////4" ), Create_SrackInfo( ) );
	printerDirector->info( pathTools::normalPathSeparatorToPath( "1/2//3/////4" ), Create_SrackInfo( ) );
	pathTools::pathTree pathTree( "..../123/456" );
	if( pathTree.appSubPath( "123/123/45" ) == false ) {
		printerDirector->error( QObject::tr( "123/123/45 配置异常" ), Create_SrackInfo( ) );
	} else
		printerDirector->info( pathTree.toQString( ), Create_SrackInfo( ) );

	if( pathTree.appSubPath( "123/784/45" ) == false ) {
		printerDirector->error( QObject::tr( "123/123/45 配置异常" ), Create_SrackInfo( ) );
	} else
		printerDirector->info( pathTree.toQString( ), Create_SrackInfo( ) );

	if( pathTree.appSubPath( "123/784/1" ) == false ) {
		printerDirector->error( QObject::tr( "123/123/1 配置异常" ), Create_SrackInfo( ) );
	} else
		printerDirector->info( pathTree.toQString( ), Create_SrackInfo( ) );
}
void TestCodeSources::testAppMoveWidget( ) {

	auto instancePtr = Application::getInstancePtr( );
	auto printerDirector = instancePtr->getPrinterDirector( );
	if( instancePtr->widgetMoveTargetDispyer( 1 ) )
		printerDirector->info( QObject::tr( "移动成功到 0 号屏幕" ), Create_SrackInfo( ) );
	else
		printerDirector->info( QObject::tr( "移动失败，0 号屏幕不存在" ), Create_SrackInfo( ) );
	if( instancePtr->widgetAllMoveTargetDispyer( 0 ) )
		printerDirector->info( QObject::tr( "全部移动成功到 0 号屏幕" ), Create_SrackInfo( ) );
	else
		printerDirector->info( QObject::tr( "全部移动失败，0 号屏幕不存在" ), Create_SrackInfo( ) );
}
/// @brief 运行测试函数
/// @return 返回 true，表示继续程序，否则退出 
bool TestCodeSources::testAll( ) {
	//TestCodeSources::testEnumConver( );
	//TestCodeSources::testVarGener( );
	//TestCodeSources::testAppFile( );
	//TestCodeSources::testAppSaveBin( );
	//TestCodeSources::testAppMoveWidget( );
	//return false;
	//QMetaEnum metaEnum = QMetaEnum::fromType< QStandardPaths::StandardLocation >( );
	//for( int i = 0; i < metaEnum.keyCount( ); ++i ) {
	//	qDebug( ) << "(" << metaEnum.key( i ) << "," << metaEnum.value( i ) << "):" << QStandardPaths::writableLocation( ( QStandardPaths::StandardLocation ) metaEnum.value( i ) );
	//}
	return true;
}
