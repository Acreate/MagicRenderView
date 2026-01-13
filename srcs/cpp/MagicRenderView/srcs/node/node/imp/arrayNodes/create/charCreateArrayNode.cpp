#include "charCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/charVectorOutputPort.h>

CharCreateArrayNode::CharCreateArrayNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool CharCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ArrayNode::initEx( parent );
}
bool CharCreateArrayNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool CharCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool CharCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	outputVarPtr->clear( );
	return true;
}
