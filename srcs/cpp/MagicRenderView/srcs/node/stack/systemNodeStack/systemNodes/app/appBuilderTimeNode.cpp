#include "appBuilderTimeNode.h"

#include <app/application.h>
#include <cmake_include_to_c_cpp_header_env.h>
#include <director/varDirector.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/dateTimeOutputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QDir>
#include <QLibraryInfo>
#include <QVersionNumber>

AppBuilderTimeNode::AppBuilderTimeNode( const QString &node_name ) : ProcessNode( node_name ) {
	appNameVarPtr = nullptr;
	appPathVarPtr = nullptr;
	builderTimeVarPtr = nullptr;
	builderToolVarPtr = nullptr;
	versionVarPtr = nullptr;
	appStartTimeVarPtr = nullptr;
	isShared = nullptr;
	sep = nullptr;
}
bool AppBuilderTimeNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "名称" ), appNameOutputPort, appNameVarPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "路径" ), appPathOutputPort, appPathVarPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "路径分隔符" ), pathSepOutputPort, sep ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "启动时间" ), appStartTimeOutputPort, appStartTimeVarPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "编译时间" ), builderTimeOutputPort, builderTimeVarPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "编译工具" ), builderToolOutputPort, builderToolVarPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "软件版本" ), versionOutputPort, versionVarPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "是否动态库" ), isSharedOutputPort, isShared ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppBuilderTimeNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppBuilderTimeNode::readyNodeRunData( ) {
	return true;
}
bool AppBuilderTimeNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
	*sep = QDir::separator( );
	return true;
}
