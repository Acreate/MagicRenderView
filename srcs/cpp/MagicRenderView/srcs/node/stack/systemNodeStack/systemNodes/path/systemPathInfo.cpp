#include "systemPathInfo.h"

#include <app/application.h>
#include <QStandardPaths>
#include <director/printerDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../director/varDirector.h"
#include "../../../../nodeTools/nodeTools.h"

void SystemPathInfo::writableLocationPath( QString &result_path, const QStandardPaths::StandardLocation &standard_location_type ) {
	result_path = QStandardPaths::writableLocation( standard_location_type );
}
SystemPathInfo::SystemPathInfo( const QString &node_name ) : ProcessNode( node_name ) {
	fontsPathPtr = nullptr;
	applicationsPathPtr = nullptr;
	appLocalDataPathPtr = nullptr;
	genericDataPathPtr = nullptr;
	runtimePathPtr = nullptr;
	configPathPtr = nullptr;
	genericCachePathPtr = nullptr;
	genericConfigPathPtr = nullptr;
	appConfigPathPtr = nullptr;
	publicSharePathPtr = nullptr;
	templatesPathPtr = nullptr;
	statePathPtr = nullptr;
	genericStatePathPtr = nullptr;
	desktopPathPtr = nullptr;
	documentsPathPtr = nullptr;
	downloadsPathPtr = nullptr;
	picturesPathPtr = nullptr;
	musicPathPtr = nullptr;
	videosPathPtr = nullptr;
	homePathPtr = nullptr;
	appDataPathPtr = nullptr;
	cachePathPtr = nullptr;
	tempPathPtr = nullptr;
}
bool SystemPathInfo::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户桌面路径" ), desktopPathOutputPortPtr, desktopPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户文档路径" ), documentsPathOutputPortPtr, documentsPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "系统字体路径" ), fontsPathOutputPortPtr, fontsPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户开始菜单路径" ), applicationsPathOutputPortPtr, applicationsPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户音乐路径" ), musicPathOutputPortPtr, musicPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户视频路径" ), videosPathOutputPortPtr, videosPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户图像路径" ), picturesPathOutputPortPtr, picturesPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户临时路径" ), tempPathOutputPortPtr, tempPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户家路径" ), homePathOutputPortPtr, homePathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户使用该软件时使用的软件数据路径" ), appLocalDataPathOutputPortPtr, appLocalDataPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户使用该软件时使用的软件缓存路径" ), cachePathOutputPortPtr, cachePathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户软件路径" ), genericDataPathOutputPortPtr, genericDataPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户家目录" ), runtimePathOutputPortPtr, runtimePathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户使用该软件时使用的软件配置路径" ), configPathOutputPortPtr, configPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户下载数据保存路径" ), downloadsPathOutputPortPtr, downloadsPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户缓存路径" ), genericCachePathOutputPortPtr, genericCachePathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户软件数据路径" ), genericConfigPathOutputPortPtr, genericConfigPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户使用该软件可移动数据存放路径" ), appDataPathOutputPortPtr, appDataPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户使用该软件可存放配置文件路径" ), appConfigPathOutputPortPtr, appConfigPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "公共路径" ), publicSharePathOutputPortPtr, publicSharePathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户模板路径" ), templatesPathOutputPortPtr, templatesPathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户的应用程序数据和缓存路径" ), statePathOutputPortPtr, statePathPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "当前用户的应用程序共享数据和缓存路径" ), genericStatePathOutputPortPtr, genericStatePathPtr ) == false )
			return false;

		return true;
	};
	return ProcessNode::initEx( parent );
}
bool SystemPathInfo::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool SystemPathInfo::readyNodeRunData( ) {
	writableLocationPath( *desktopPathPtr, QStandardPaths::DesktopLocation );
	writableLocationPath( *documentsPathPtr, QStandardPaths::DocumentsLocation );
	writableLocationPath( *fontsPathPtr, QStandardPaths::FontsLocation );
	writableLocationPath( *applicationsPathPtr, QStandardPaths::ApplicationsLocation );
	writableLocationPath( *musicPathPtr, QStandardPaths::MusicLocation );
	writableLocationPath( *videosPathPtr, QStandardPaths::MoviesLocation );
	writableLocationPath( *picturesPathPtr, QStandardPaths::PicturesLocation );
	writableLocationPath( *tempPathPtr, QStandardPaths::TempLocation );
	writableLocationPath( *homePathPtr, QStandardPaths::HomeLocation );
	writableLocationPath( *appLocalDataPathPtr, QStandardPaths::AppLocalDataLocation );
	writableLocationPath( *cachePathPtr, QStandardPaths::CacheLocation );
	writableLocationPath( *genericDataPathPtr, QStandardPaths::GenericDataLocation );
	writableLocationPath( *runtimePathPtr, QStandardPaths::RuntimeLocation );
	writableLocationPath( *configPathPtr, QStandardPaths::ConfigLocation );
	writableLocationPath( *downloadsPathPtr, QStandardPaths::DownloadLocation );
	writableLocationPath( *genericCachePathPtr, QStandardPaths::GenericCacheLocation );
	writableLocationPath( *genericConfigPathPtr, QStandardPaths::GenericConfigLocation );
	writableLocationPath( *appDataPathPtr, QStandardPaths::AppDataLocation );
	writableLocationPath( *appConfigPathPtr, QStandardPaths::AppConfigLocation );
	writableLocationPath( *publicSharePathPtr, QStandardPaths::PublicShareLocation );
	writableLocationPath( *templatesPathPtr, QStandardPaths::TemplatesLocation );
	writableLocationPath( *statePathPtr, QStandardPaths::StateLocation );
	writableLocationPath( *genericStatePathPtr, QStandardPaths::GenericStateLocation );
	return true;
}
bool SystemPathInfo::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
