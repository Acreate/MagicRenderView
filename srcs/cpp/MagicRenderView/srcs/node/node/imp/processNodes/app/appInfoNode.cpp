#include "appInfoNode.h"

#include <app/application.h>
#include <director/printerDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

#include "../../../../../director/varDirector.h"

AppInfoNode::AppInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	appNameVarPtr = nullptr;
	appPathVarPtr = nullptr;
	builderTimeVarPtr = nullptr;
	builderToolVarPtr = nullptr;
	versionVarPtr = nullptr;
}
bool AppInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendOutputPortType< >( tr( "名称" ), appNameOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "路径" ), appPathOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "编译时间" ), builderTimeOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "编译工具" ), builderToolOutputPort ) == false )
			return false;
		if( appendOutputPortType< >( tr( "软件版本" ), versionOutputPort ) == false )
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
	// todo : 未实现
	return false;
}
