#include "uIntCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/uIntVectorOutputPort.h>

UIntCreateArrayNode::UIntCreateArrayNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool UIntCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ArrayNode::initEx( parent );
}
bool UIntCreateArrayNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool UIntCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	outputVarPtr->clear( );
	return true;
}
