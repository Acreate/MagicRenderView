#include "colorCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

ColorCreateUnityNode::ColorCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = QColor( 0, 0, 0, 255 );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ColorCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool ColorCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
