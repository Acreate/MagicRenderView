#include "uIntCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/uIntVectorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

UIntCreateArrayNode::UIntCreateArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool UIntCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool UIntCreateArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool UIntCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
