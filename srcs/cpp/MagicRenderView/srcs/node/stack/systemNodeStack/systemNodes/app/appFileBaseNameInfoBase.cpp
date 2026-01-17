#include "appFileBaseNameInfoBase.h"

#include <app/application.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <QLibraryInfo>

AppFileBaseNameInfoBase::AppFileBaseNameInfoBase( const QString &node_name ) : ProcessNode( node_name ) {
	outputPortPtr = nullptr;
}
bool AppFileBaseNameInfoBase::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		QString nodeTypeName;
		nodeToolsPtr->getVirtualNormalPathLastName( this, nodeTypeName );
		if( nodeToolsPtr->appendOutputPortType( this, nodeTypeName, outputPortPtr, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool AppFileBaseNameInfoBase::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool AppFileBaseNameInfoBase::readyNodeRunData( ) {
	*outputVarPtr = Application::getInstancePtr( )->applicationName( );
	return true;
}
bool AppFileBaseNameInfoBase::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
