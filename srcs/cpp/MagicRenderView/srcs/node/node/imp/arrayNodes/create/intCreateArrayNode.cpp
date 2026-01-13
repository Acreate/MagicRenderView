#include "intCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/intVectorOutputPort.h>

IntCreateArrayNode::IntCreateArrayNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool IntCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ArrayNode::initEx( parent );
}
bool IntCreateArrayNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool IntCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	outputVarPtr->clear( );
	return true;
}
