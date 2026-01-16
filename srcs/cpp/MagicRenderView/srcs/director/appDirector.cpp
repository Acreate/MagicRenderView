#include "appDirector.h"

#include <qfile.h>
#include <QFileDialog>

#include "../app/application.h"
#include "../srack/srackInfo.h"
#include "../tools/path.h"
#include "nodeDirector.h"
#include "printerDirector.h"
#include "varDirector.h"
bool AppDirector::syncProjectToFile( ) {
	if( currentProjectAbsoluteFilePathName.isEmpty( ) || path::hasFile( currentProjectAbsoluteFilePathName ) == false )
		return false;
	QFile file( currentProjectAbsoluteFilePathName );
	if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Truncate ) == false )
		return false;
	std::vector< uint8_t > resultData;
	if( nodeDirector->toUint8VectorData( resultData ) == false )
		return false;
	size_t writeCount = resultData.size( );
	if( writeCount == 0 )
		return false;
	char *data = ( char * ) resultData.data( );
	if( file.write( data, writeCount ) != writeCount )
		return false;
	return true;
}
bool AppDirector::syncFileToProject( ) {
	QString openFilePath = currentProjectWorkPath + '/' + currentProjectName;
	QFile file( openFilePath );
	if( file.open( QIODeviceBase::ReadWrite ) == false )
		return false;
	QByteArray byteArray = file.readAll( );
	size_t readCount = byteArray.size( );
	if( readCount == 0 )
		return false;
	char *data = byteArray.data( );
	auto converData = ( uint8_t * ) data;
	size_t userCount = sizeof( data[ 0 ] ) / sizeof( uint8_t );
	readCount = userCount * readCount;
	if( nodeDirector->formUint8ArrayData( userCount, converData, readCount ) == false )
		return false;
	return true;
}
void AppDirector::saveThisDataToAppInstance( ) {
	VarDirector varDirector;
	QString *strVar;
	std::vector< QString > *strVectorVar;
	if( varDirector.init( ) == false ) {
		printerDirector->info( tr( "初始化 VarDirector 失败" ), Create_SrackInfo( ) );
		return;
	}
	if( varDirector.create( strVar ) == false ) {
		printerDirector->info( tr( "创建 QString 失败" ), Create_SrackInfo( ) );
		return;
	}
	if( varDirector.create( strVectorVar ) == false ) {
		printerDirector->info( tr( "创建 std::vector<QString> 失败" ), Create_SrackInfo( ) );
		return;
	}
	std::vector< uint8_t > result;
	*strVar = currentProjectWorkPath;
	if( varDirector.toVector( strVar, result ) == false )
		printerDirector->info( tr( "AppDirector::currentProjectWorkPath 序列化失败" ), Create_SrackInfo( ) );
	else if( application->setVar( tr( "AppDirector::currentProjectWorkPath" ), result ) == false )
		printerDirector->info( tr( "AppDirector::currentProjectWorkPath 保存失败" ), Create_SrackInfo( ) );

	*strVectorVar = projectHistory;
	if( varDirector.toVector( strVectorVar, result ) == false )
		printerDirector->info( tr( "AppDirector::currentProjectHistory 序列化失败" ), Create_SrackInfo( ) );
	else if( application->setVar( tr( "AppDirector::currentProjectHistory" ), result ) == false )
		printerDirector->info( tr( "AppDirector::currentProjectHistory 保存失败" ), Create_SrackInfo( ) );

}
void AppDirector::loadThisDataToAppInstance( ) {
	VarDirector varDirector;
	QString *strVar;
	std::vector< QString > *strVectorVar;
	QString *projectArrayPtr;
	size_t projectIndex;
	QString *data;
	size_t index;
	void *converPtr;
	std::vector< uint8_t > result;
	size_t count;
	projectHistory.clear( );
	if( varDirector.init( ) == false ) {
		printerDirector->info( tr( "初始化 VarDirector 失败" ), Create_SrackInfo( ) );
		return;
	}
	if( varDirector.create( strVar ) == false ) {
		printerDirector->info( tr( "创建 QString 失败" ), Create_SrackInfo( ) );
		return;
	}
	if( varDirector.create( strVectorVar ) == false ) {
		printerDirector->info( tr( "创建 std::vector<QString> 失败" ), Create_SrackInfo( ) );
		return;
	}

	// 获取 currentProjectWorkPath
	converPtr = strVar;
	application->getVar( tr( "AppDirector::currentProjectWorkPath" ), result );
	if( varDirector.toVar( count, result.data( ), result.size( ), converPtr ) == true )
		currentProjectWorkPath = *strVar;

	converPtr = strVectorVar;
	application->getVar( tr( "AppDirector::currentProjectHistory" ), result );
	if( varDirector.toVar( count, result.data( ), result.size( ), converPtr ) == true ) {
		count = strVectorVar->size( );
		std::list< QString > buffList;
		projectIndex = 0;
		data = strVectorVar->data( );
		for( index = 0; index < count; ++index )
			if( path::hasFile( data[ index ] ) ) {
				buffList.emplace_back( data[ index ] );
				++projectIndex;
			}
		// 匹配上次打开文件
		std::list< QString >::iterator listIterator;
		std::list< QString >::iterator end;

		for( ; listIterator != end; ++listIterator )
			if( *listIterator == currentProjectName ) {
				buffList.erase( listIterator );
				buffList.emplace_front( currentProjectName );
				break;
			}
		projectIndex = buffList.size( );
		if( projectIndex ) {
			listIterator = buffList.begin( );
			projectHistory.resize( projectIndex );
			projectArrayPtr = projectHistory.data( );
			for( index = 0; index < count; ++index, ++listIterator )
				projectArrayPtr[ index ] = *listIterator;
		}
	}
}
void AppDirector::appendProjectPath( const QString &append_project_file_path ) {
	size_t count = projectHistory.size( );
	QString *projectHistoryArray;
	size_t index;
	if( count ) {
		projectHistoryArray = projectHistory.data( );
		for( index = 0; index < count; ++index )
			if( projectHistoryArray[ index ] == append_project_file_path )
				return;
	}
	projectHistory.emplace_back( append_project_file_path );
}
AppDirector::~AppDirector( ) {
	saveThisDataToAppInstance( );
}
bool AppDirector::init( ) {
	application = Application::getInstancePtr( );
	printerDirector = application->getPrinterDirector( );
	nodeDirector = application->getNodeDirector( );

	loadThisDataToAppInstance( );
	return true;
}
bool AppDirector::clearAppProjectInfo( QWidget *parent ) {
	if( nodeDirector->init( ) == false )
		return false;
	return true;
}
bool AppDirector::closeAppProject( QWidget *parent ) {
	if( nodeDirector->init( ) == false )
		return false;
	currentProjectWorkPath.clear( );
	currentProjectName.clear( );
	return true;
}
bool AppDirector::saveAppProject( QWidget *parent ) {
	if( currentProjectAbsoluteFilePathName.isEmpty( ) )
		return saveAsAppProject( parent );

	if( path::createDir( currentProjectWorkPath ) == false )
		return false;
	return syncProjectToFile( );
}
bool AppDirector::saveAsAppProject( QWidget *parent ) {
	QString saveFileName;
	if( currentProjectAbsoluteFilePathName.isEmpty( ) || path::hasFile( currentProjectAbsoluteFilePathName ) == false )
		saveFileName = QFileDialog::getSaveFileName( parent, tr( "保存项目" ), QDir::currentPath( ), tr( "魔力艺术 (*.mr *.mrv *.MagucRender *.MagucRenderView)" ) );
	else
		saveFileName = QFileDialog::getSaveFileName( parent, tr( "保存项目" ), currentProjectAbsoluteFilePathName, tr( "魔力艺术 (*.mr *.mrv *.MagucRender *.MagucRenderView)" ) );

	if( saveFileName.isEmpty( ) )
		return false;
	QFileInfo saveInfo( saveFileName );
	currentProjectWorkPath = saveInfo.dir( ).absolutePath( );
	currentProjectName = saveInfo.fileName( );
	currentProjectAbsoluteFilePathName = saveInfo.absoluteFilePath( );
	appendProjectPath( currentProjectAbsoluteFilePathName );
	return syncProjectToFile( );
}
bool AppDirector::updateAppProject( QWidget *parent ) {
	if( syncProjectToFile( ) == false )
		return false;
	if( syncFileToProject( ) == false )
		return false;
	return true;
}
bool AppDirector::reloadAppProject( QWidget *parent ) {
	if( syncFileToProject( ) == false )
		return false;
	return true;
}
bool AppDirector::loadAppPorject( QWidget *parent ) {
	QString openFilePath;
	if( currentProjectAbsoluteFilePathName.isEmpty( ) || path::hasFile( currentProjectAbsoluteFilePathName ) == false )
		openFilePath = QFileDialog::getOpenFileName( parent, tr( "打开文件" ), QDir::currentPath( ), tr( "魔力艺术 (*.mr *.mrv *.MagucRender *.MagucRenderView)" ) );
	else
		openFilePath = QFileDialog::getOpenFileName( parent, tr( "打开文件" ), currentProjectAbsoluteFilePathName, tr( "魔力艺术 (*.mr *.mrv *.MagucRender *.MagucRenderView)" ) );
	if( openFilePath.isEmpty( ) || path::hasFile( openFilePath ) == false )
		return false;
	QFileInfo saveInfo( openFilePath );
	currentProjectWorkPath = saveInfo.dir( ).absolutePath( );
	currentProjectName = saveInfo.fileName( );
	currentProjectAbsoluteFilePathName = saveInfo.absoluteFilePath( );
	appendProjectPath( currentProjectAbsoluteFilePathName );
	return syncFileToProject( );
}
