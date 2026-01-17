#include "appIsShredBuilderInfoNode.h"

#include <app/application.h>
#include <node/nodeTools/nodeTools.h>
#include <QLibraryInfo>

#include "../../../../port/outputPort/unity/intOutputPort.h"

AppIsShredBuilderInfoNode::AppIsShredBuilderInfoNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputPortPtr = nullptr;
}
bool AppIsShredBuilderInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, outputPortPtr, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppIsShredBuilderInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppIsShredBuilderInfoNode::readyNodeRunData( ) {
	*outputVarPtr = Application::getInstancePtr( )->getQTBuilderIsShared( );
	return true;
}
bool AppIsShredBuilderInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
