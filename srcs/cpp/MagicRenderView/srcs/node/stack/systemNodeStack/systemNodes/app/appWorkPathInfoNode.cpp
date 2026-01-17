#include "appWorkPathInfoNode.h"

#include <app/application.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QDir>
#include <QLibraryInfo>

AppWorkPathInfoNode::AppWorkPathInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputPortPtr = nullptr;
}
bool AppWorkPathInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, outputPortPtr, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppWorkPathInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppWorkPathInfoNode::readyNodeRunData( ) {
	*outputVarPtr = QDir::currentPath( );
	return true;
}
bool AppWorkPathInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
