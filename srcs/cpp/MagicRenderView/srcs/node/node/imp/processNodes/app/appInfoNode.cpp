#include "appInfoNode.h"

#include <app/application.h>
#include <director/varDirector.h>
#include <node/port/outputPort/unity/dateTimeOutputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QLibraryInfo>
#include <QVersionNumber>
#include <tools/infoTool.h>
#include <cmake_include_to_c_cpp_header_env.h>

#include "../../../../port/outputPort/unity/intOutputPort.h"

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
		if( appendOutputPortType< >( tr( "名称" ), appNameOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "路径" ), appPathOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "启动时间" ), appStartTimeOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "编译时间" ), builderTimeOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "编译工具" ), builderToolOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "软件版本" ), versionOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "是否动态库" ), isSharedOutputPort ) == false )
			return false;
		if( appNameVarPtr )
			varDirector->release( appNameVarPtr );
		if( varDirector->create( appNameVarPtr ) == false )
			return false;
		if( appPathVarPtr )
			varDirector->release( appPathVarPtr );
		if( varDirector->create( appPathVarPtr ) == false )
			return false;
		if( builderTimeVarPtr )
			varDirector->release( builderTimeVarPtr );
		if( varDirector->create( builderTimeVarPtr ) == false )
			return false;
		if( builderToolVarPtr )
			varDirector->release( builderToolVarPtr );
		if( varDirector->create( builderToolVarPtr ) == false )
			return false;
		if( versionVarPtr )
			varDirector->release( versionVarPtr );
		if( varDirector->create( versionVarPtr ) == false )
			return false;
		if( appStartTimeVarPtr )
			varDirector->release( appStartTimeVarPtr );
		if( varDirector->create( appStartTimeVarPtr ) == false )
			return false;
		if( isShared )
			varDirector->release( isShared );
		if( varDirector->create( isShared ) == false )
			return false;
		if( setPortVar( appNameOutputPort, appNameVarPtr ) == false )
			return false;
		if( setPortVar( appPathOutputPort, appPathVarPtr ) == false )
			return false;
		if( setPortVar( builderTimeOutputPort, builderTimeVarPtr ) == false )
			return false;
		if( setPortVar( builderToolOutputPort, builderToolVarPtr ) == false )
			return false;
		if( setPortVar( versionOutputPort, versionVarPtr ) == false )
			return false;
		if( setPortVar( appStartTimeOutputPort, appStartTimeVarPtr ) == false )
			return false;
		if( setPortVar( isSharedOutputPort, isShared ) == false )
			return false;
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
bool AppInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
