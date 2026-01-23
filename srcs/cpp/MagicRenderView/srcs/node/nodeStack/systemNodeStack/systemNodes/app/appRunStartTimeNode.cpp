#include "appRunStartTimeNode.h"

#include <app/application.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QLibraryInfo>

#include "../../../../port/outputPort/unity/dateTimeOutputPort.h"

Def_Entity_NodeTypeName_Function( AppRunStartTimeNode, Node::tr( "软件/起始运行时间" ) );

AppRunStartTimeNode::AppRunStartTimeNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputPortPtr = nullptr;
}
bool AppRunStartTimeNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, outputPortPtr, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppRunStartTimeNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppRunStartTimeNode::readyNodeRunData( ) {
	*outputVarPtr = *Application::getInstancePtr( )->getAppInitRunDataTime( );
	return true;
}
bool AppRunStartTimeNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
