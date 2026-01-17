#include "runArgInfoNode.h"

#include <app/application.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QLibraryInfo>

RunArgInfoNode::RunArgInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputPortPtr = nullptr;
}
bool RunArgInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, outputPortPtr, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool RunArgInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool RunArgInfoNode::readyNodeRunData( ) {
	QList< QString > arguments = Application::getInstancePtr( )->arguments( );
	QList< QString > runArgs( arguments.begin( ) + 1, arguments.end( ) );
	*outputVarPtr = runArgs.join( " " );
	return true;
}
bool RunArgInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
