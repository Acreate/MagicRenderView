#include "stringCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/stringVectorOutputPort.h>

StringCreateArrayNode::StringCreateArrayNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ArrayNode::initEx( parent );
}
bool StringCreateArrayNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool StringCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	outputVarPtr->clear( );
	return true;
}
