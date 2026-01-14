#include "appInfoNode.h"

#include <app/application.h>
#include <cmake_include_to_c_cpp_header_env.h>
#include <director/varDirector.h>
#include <node/port/outputPort/unity/dateTimeOutputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QLibraryInfo>
#include <QVersionNumber>
#include <tools/infoTool.h>

AppInfoNode::AppInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	appNameVarPtr = nullptr;
	appPathVarPtr = nullptr;
	builderTimeVarPtr = nullptr;
	builderToolVarPtr = nullptr;
	versionVarPtr = nullptr;
	appStartTimeVarPtr = nullptr;
	isShared = nullptr;
}
bool AppInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "名称" ), appNameOutputPort, appNameVarPtr );
		Def_AppendBindVarOutputPortType( tr( "路径" ), appPathOutputPort, appPathVarPtr );
		Def_AppendBindVarOutputPortType( tr( "启动时间" ), appStartTimeOutputPort, appStartTimeVarPtr );
		Def_AppendBindVarOutputPortType( tr( "编译时间" ), builderTimeOutputPort, builderTimeVarPtr );
		Def_AppendBindVarOutputPortType( tr( "编译工具" ), builderToolOutputPort, builderToolVarPtr );
		Def_AppendBindVarOutputPortType( tr( "软件版本" ), versionOutputPort, versionVarPtr );
		Def_AppendBindVarOutputPortType( tr( "是否动态库" ), isSharedOutputPort, isShared );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppInfoNode::readyNodeRunData( ) {
	return true;
}
bool AppInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	Application *instancePtr = Application::getInstancePtr( );
	*appNameVarPtr = instancePtr->applicationName( );
	*appPathVarPtr = instancePtr->applicationFilePath( );
	*builderToolVarPtr = tr( "QT %1 (%2.%3.%4.%5)" ).arg( QT_VERSION_STR ).arg( cmake_value_CMAKE_SYSTEM ).arg( cmake_value_CMAKE_SYSTEM_PROCESSOR ).arg( Builder_Tools_MSVC ? "MSVC" : Builder_Tools_GNU ? "GNU" : Builder_Tools_Clang ? "Clang" : "null" ).arg( cmake_value_CMAKE_BUILD_TYPE );
	*builderTimeVarPtr = QDateTime(
		QDate::fromString( __DATE__, "MMM dd yyyy" ),
		QTime::fromString( __TIME__, "hh:mm:ss" )
		);
	auto versionNumber = QLibraryInfo::version( );
	*versionVarPtr = tr( "%1.%2.%3" ).arg( versionNumber.majorVersion( ) ).arg( versionNumber.minorVersion( ) ).arg( versionNumber.microVersion( ) );
	*appStartTimeVarPtr = *instancePtr->getAppInitRunDataTime( );
	*isShared = QLibraryInfo::isSharedBuild( );
	return true;
}
