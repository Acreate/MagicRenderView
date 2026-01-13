#include "systemPathInfo.h"

#include <app/application.h>
#include <QStandardPaths>
#include <director/printerDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../director/varDirector.h"

bool SystemPathInfo::oldClassInit( ) {
	Def_AppendBindVarOutputPortType( tr( "当前用户桌面路径" ), desktopPathOutputPortPtr, desktopPathPtr );
	// ( DesktopLocation , 0 ): "C:/Users/%SUER%/Desktop"
	*desktopPathPtr = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户文档路径" ), documentsPathOutputPortPtr, documentsPathPtr );
	// ( DocumentsLocation , 1 ): "C:/Users/%SUER%/Documents"
	*documentsPathPtr = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );

	Def_AppendBindVarOutputPortType( tr( "系统字体路径" ), fontsPathOutputPortPtr, fontsPathPtr );
	// ( FontsLocation , 2 ): "C:/Windows/Fonts"
	*fontsPathPtr = QStandardPaths::writableLocation( QStandardPaths::FontsLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户开始菜单路径" ), applicationsPathOutputPortPtr, applicationsPathPtr );
	// ( ApplicationsLocation , 3 ): "C:/Users/%SUER%/AppData/Roaming/Microsoft/Windows/Start Menu/Programs"
	*applicationsPathPtr = QStandardPaths::writableLocation( QStandardPaths::ApplicationsLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户音乐路径" ), musicPathOutputPortPtr, musicPathPtr );
	// ( MusicLocation , 4 ): "C:/Users/%SUER%/Music"
	*musicPathPtr = QStandardPaths::writableLocation( QStandardPaths::MusicLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户视频路径" ), videosPathOutputPortPtr, videosPathPtr );
	// ( MoviesLocation , 5 ): "C:/Users/%SUER%/Videos"
	*videosPathPtr = QStandardPaths::writableLocation( QStandardPaths::MoviesLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户图像路径" ), picturesPathOutputPortPtr, picturesPathPtr );
	// ( PicturesLocation , 6 ): "C:/Users/%SUER%/Pictures"
	*picturesPathPtr = QStandardPaths::writableLocation( QStandardPaths::PicturesLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户临时路径" ), tempPathOutputPortPtr, tempPathPtr );
	// ( TempLocation , 7 ): "C:/Users/%SUER%/AppData/Local/Temp"
	*tempPathPtr = QStandardPaths::writableLocation( QStandardPaths::TempLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户家路径" ), homePathOutputPortPtr, homePathPtr );
	// ( HomeLocation , 8 ): "C:/Users/%SUER%"
	*homePathPtr = QStandardPaths::writableLocation( QStandardPaths::HomeLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件时使用的软件数据路径" ), appLocalDataPathOutputPortPtr, appLocalDataPathPtr );
	// ( AppLocalDataLocation , 9 ): "C:/Users/%SUER%/AppData/Local/MagicRenderView"
	*appLocalDataPathPtr = QStandardPaths::writableLocation( QStandardPaths::AppLocalDataLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件时使用的软件缓存路径" ), cachePathOutputPortPtr, cachePathPtr );
	// ( CacheLocation , 10 ): "C:/Users/%SUER%/AppData/Local/MagicRenderView/cache"
	*cachePathPtr = QStandardPaths::writableLocation( QStandardPaths::CacheLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户软件路径" ), genericDataPathOutputPortPtr, genericDataPathPtr );
	// ( GenericDataLocation , 11 ): "C:/Users/%SUER%/AppData/Local"
	*genericDataPathPtr = QStandardPaths::writableLocation( QStandardPaths::GenericDataLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户家目录" ), runtimePathOutputPortPtr, runtimePathPtr );
	// ( RuntimeLocation , 12 ): "C:/Users/%SUER%"
	*runtimePathPtr = QStandardPaths::writableLocation( QStandardPaths::RuntimeLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件时使用的软件配置路径" ), configPathOutputPortPtr, configPathPtr );
	// ( ConfigLocation , 13 ): "C:/Users/%SUER%/AppData/Local/MagicRenderView"
	*configPathPtr = QStandardPaths::writableLocation( QStandardPaths::ConfigLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户下载数据保存路径" ), downloadsPathOutputPortPtr, downloadsPathPtr );
	// ( DownloadLocation , 14 ): "C:/Users/%SUER%/Downloads"
	*downloadsPathPtr = QStandardPaths::writableLocation( QStandardPaths::DownloadLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户缓存路径" ), genericCachePathOutputPortPtr, genericCachePathPtr );
	// ( GenericCacheLocation , 15 ): "C:/Users/%SUER%/AppData/Local/cache"
	*genericCachePathPtr = QStandardPaths::writableLocation( QStandardPaths::GenericCacheLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户软件数据路径" ), genericConfigPathOutputPortPtr, genericConfigPathPtr );
	// ( GenericConfigLocation , 16 ): "C:/Users/%SUER%/AppData/Local"
	*genericConfigPathPtr = QStandardPaths::writableLocation( QStandardPaths::GenericConfigLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件可移动数据存放路径" ), appDataPathOutputPortPtr, appDataPathPtr );
	// ( AppDataLocation , 17 ): "C:/Users/%SUER%/AppData/Roaming/MagicRenderView"
	*appDataPathPtr = QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件可存放配置文件路径" ), appConfigPathOutputPortPtr, appConfigPathPtr );
	// ( AppConfigLocation , 18 ): "C:/Users/%SUER%/AppData/Local/MagicRenderView"
	*appConfigPathPtr = QStandardPaths::writableLocation( QStandardPaths::AppConfigLocation );

	Def_AppendBindVarOutputPortType( tr( "公共路径" ), publicSharePathOutputPortPtr, publicSharePathPtr );
	// ( PublicShareLocation , 19 ): "C:/Users/Public"
	*publicSharePathPtr = QStandardPaths::writableLocation( QStandardPaths::PublicShareLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户模板路径" ), templatesPathOutputPortPtr, templatesPathPtr );
	// ( TemplatesLocation , 20 ): "C:/Users/%SUER%/AppData/Roaming/Microsoft/Windows/Templates"
	*templatesPathPtr = QStandardPaths::writableLocation( QStandardPaths::TemplatesLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户的应用程序数据和缓存路径" ), statePathOutputPortPtr, statePathPtr );
	// ( StateLocation , 21 ): "C:/Users/%SUER%/AppData/Local/MagicRenderView/State"
	*statePathPtr = QStandardPaths::writableLocation( QStandardPaths::StateLocation );

	Def_AppendBindVarOutputPortType( tr( "当前用户的应用程序共享数据和缓存路径" ), genericStatePathOutputPortPtr, genericStatePathPtr );
	// ( GenericStateLocation , 22 ): "C:/Users/%SUER%/AppData/Local/State"
	*genericStatePathPtr = QStandardPaths::writableLocation( QStandardPaths::GenericStateLocation );
	return true;
}
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
		Def_AppendBindVarOutputPortType( tr( "当前用户桌面路径" ), desktopPathOutputPortPtr, desktopPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户文档路径" ), documentsPathOutputPortPtr, documentsPathPtr );
		Def_AppendBindVarOutputPortType( tr( "系统字体路径" ), fontsPathOutputPortPtr, fontsPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户开始菜单路径" ), applicationsPathOutputPortPtr, applicationsPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户音乐路径" ), musicPathOutputPortPtr, musicPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户视频路径" ), videosPathOutputPortPtr, videosPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户图像路径" ), picturesPathOutputPortPtr, picturesPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户临时路径" ), tempPathOutputPortPtr, tempPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户家路径" ), homePathOutputPortPtr, homePathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件时使用的软件数据路径" ), appLocalDataPathOutputPortPtr, appLocalDataPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件时使用的软件缓存路径" ), cachePathOutputPortPtr, cachePathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户软件路径" ), genericDataPathOutputPortPtr, genericDataPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户家目录" ), runtimePathOutputPortPtr, runtimePathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件时使用的软件配置路径" ), configPathOutputPortPtr, configPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户下载数据保存路径" ), downloadsPathOutputPortPtr, downloadsPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户缓存路径" ), genericCachePathOutputPortPtr, genericCachePathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户软件数据路径" ), genericConfigPathOutputPortPtr, genericConfigPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件可移动数据存放路径" ), appDataPathOutputPortPtr, appDataPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户使用该软件可存放配置文件路径" ), appConfigPathOutputPortPtr, appConfigPathPtr );
		Def_AppendBindVarOutputPortType( tr( "公共路径" ), publicSharePathOutputPortPtr, publicSharePathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户模板路径" ), templatesPathOutputPortPtr, templatesPathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户的应用程序数据和缓存路径" ), statePathOutputPortPtr, statePathPtr );
		Def_AppendBindVarOutputPortType( tr( "当前用户的应用程序共享数据和缓存路径" ), genericStatePathOutputPortPtr, genericStatePathPtr );

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
bool SystemPathInfo::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
