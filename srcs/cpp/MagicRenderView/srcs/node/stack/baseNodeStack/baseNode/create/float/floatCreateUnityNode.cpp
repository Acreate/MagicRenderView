#include "floatCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/floatOutputPort.h>
#include <node/nodeTools/nodeTools.h>

FloatCreateUnityNode::FloatCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool FloatCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool FloatCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool FloatCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool FloatCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
