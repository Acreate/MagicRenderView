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
	QString saveTarget = currentProjectWorkPath + '/' + currentProjectName;
	QFile file( saveTarget );
	if( file.open( QIODeviceBase::ReadWrite | QIODeviceBase::Truncate ) == false )
		return false;
	std::vector< uint8_t > resultData;
	if( nodeDirector->toUint8VectorData( resultData ) == false )
		return false;
	size_t writeCount = resultData.size( );
	if( writeCount == 0 )
		return false;
	char *data = ( char * ) resultData.data( );
	if( file.write( data, writeCount ) == writeCount )
		return true;
	return false;
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
	if( varDirector.init( ) == false ) {
		printerDirector->info( tr( "初始化 VarDirector 失败" ), Create_SrackInfo( ) );
		return;
	}
	if( varDirector.create( strVar ) == false ) {
		printerDirector->info( tr( "创建 QString 失败" ), Create_SrackInfo( ) );
		return;
	}
	*strVar = currentProjectWorkPath;
	std::vector< uint8_t > result;
	if( varDirector.toVector( strVar, result ) == false )
		printerDirector->info( tr( "AppDirector::currentProjectWorkPath 序列化失败" ), Create_SrackInfo( ) );
	else if( application->setVar( tr( "AppDirector::currentProjectWorkPath" ), result ) == false )
		printerDirector->info( tr( "AppDirector::currentProjectWorkPath 保存失败" ), Create_SrackInfo( ) );
	//*strVar = currentProjectName;
	//if( varDirector.toVector( strVar, result ) == false )
	//	printerDirector->info( tr( "AppDirector::currentProjectName 序列化失败" ), Create_SrackInfo( ) );
	//else if( application->setVar( tr( "AppDirector::currentProjectName" ), result ) == false )
	//	printerDirector->info( tr( "AppDirector::currentProjectName 保存失败" ), Create_SrackInfo( ) );
}
void AppDirector::loadThisDataToAppInstance( ) {
	VarDirector varDirector;
	QString *strVar;
	if( varDirector.init( ) == false ) {
		printerDirector->info( tr( "初始化 VarDirector 失败" ), Create_SrackInfo( ) );
		return;
	}
	if( varDirector.create( strVar ) == false ) {
		printerDirector->info( tr( "创建 QString 失败" ), Create_SrackInfo( ) );
		return;
	}
	void *converPtr = strVar;
	std::vector< uint8_t > result;
	size_t count;

	// 获取 currentProjectWorkPath
	application->getVar( tr( "AppDirector::currentProjectWorkPath" ), result );
	if( varDirector.toVar( count, result.data( ), result.size( ), converPtr ) == true )
		currentProjectWorkPath = *strVar;
	// 获取 currentProjectName
	//application->getVar( tr( "AppDirector::currentProjectName" ), result );
	//if( varDirector.toVar( count, result.data( ), result.size( ), converPtr ) == true )
	//	currentProjectName = *strVar;
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
	if( currentProjectName.isEmpty( ) || currentProjectWorkPath.isEmpty( ) )
		return saveAsAppProject( parent );

	if( path::createDir( currentProjectWorkPath ) == false )
		return false;
	return syncProjectToFile( );
}
bool AppDirector::saveAsAppProject( QWidget *parent ) {

	auto saveFileName = QFileDialog::getSaveFileName( parent, tr( "保存项目" ), QDir::currentPath( ), tr( "魔力艺术 (*.mr *.mrv *.MagucRender *.MagucRenderView)" ) );
	if( saveFileName.isEmpty( ) )
		return false;
	QFileInfo saveInfo( saveFileName );
	currentProjectWorkPath = saveInfo.dir( ).absolutePath( );
	currentProjectName = saveInfo.fileName( );
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
	QString openFilePath = currentProjectWorkPath.isEmpty( ) ? QDir::currentPath( ) : currentProjectWorkPath;
	openFilePath = QFileDialog::getOpenFileName( parent, tr( "打开文件" ), openFilePath, tr( "魔力艺术 (*.mr *.mrv *.MagucRender *.MagucRenderView)" ) );
	if( openFilePath.isEmpty( ) || path::hasFile( openFilePath ) == false )
		return false;
	QFileInfo saveInfo( openFilePath );
	currentProjectWorkPath = saveInfo.dir( ).absolutePath( );
	currentProjectName = saveInfo.fileName( );
	return syncFileToProject( );
}
