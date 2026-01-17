#include "appFilePathInfoNode.h"

#include <app/application.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QLibraryInfo>

AppFilePathInfoNode::AppFilePathInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputPortPtr = nullptr;
}
bool AppFilePathInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, outputPortPtr, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppFilePathInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppFilePathInfoNode::readyNodeRunData( ) {
	*outputVarPtr = Application::getInstancePtr( )->applicationFilePath( );
	return true;
}
bool AppFilePathInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
