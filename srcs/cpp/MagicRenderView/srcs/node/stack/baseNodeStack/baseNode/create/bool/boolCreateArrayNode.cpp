#include "boolCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/outputPort/array/boolVectorOutputPort.h>

BoolCreateArrayNode::BoolCreateArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool BoolCreateArrayNode::initEx( MainWidget *parent ) {

	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool BoolCreateArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool BoolCreateArrayNode::readyNodeRunData( ) {
	outputVarPtr->clear( );
	return true;
}
bool BoolCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
