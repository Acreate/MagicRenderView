#include "appBuilderToolNameNode.h"

#include <app/application.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QLibraryInfo>

Def_Entity_NodeTypeName_Function( AppBuilderToolNameNode, Node::tr( "软件/编译工具名称" ) );

AppBuilderToolNameNode::AppBuilderToolNameNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputPortPtr = nullptr;
}
bool AppBuilderToolNameNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, outputPortPtr, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppBuilderToolNameNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppBuilderToolNameNode::readyNodeRunData( ) {
	*outputVarPtr = Application::getInstancePtr( )->getBuilderToolInfo( );
	return true;
}
bool AppBuilderToolNameNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
