#include "appBuilderTimeNode.h"

#include <app/application.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/dateTimeOutputPort.h>
#include <QLibraryInfo>

Def_Entity_NodeTypeName_Function( AppBuilderTimeNode, Node::tr( "软件/编译时间" ) );

AppBuilderTimeNode::AppBuilderTimeNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputPortPtr = nullptr;
}
bool AppBuilderTimeNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;

		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, outputPortPtr, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppBuilderTimeNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppBuilderTimeNode::readyNodeRunData( ) {
	*outputVarPtr = *Application::getInstancePtr( )->getBuilderProjectDataTime( );
	return true;
}
bool AppBuilderTimeNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
