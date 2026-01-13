#include "colorCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/colorVectorOutputPort.h>

ColorCreateArrayNode::ColorCreateArrayNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ArrayNode::initEx( parent );
}
bool ColorCreateArrayNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool ColorCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	outputVarPtr->clear( );
	return true;
}
