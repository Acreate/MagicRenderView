#include "binCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/binVectorOutputPort.h>

BinCreateArrayNode::BinCreateArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool BinCreateArrayNode::initEx( MainWidget *parent ) {
	
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool BinCreateArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool BinCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool BinCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
