#include "stringLengthNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

StringLengthNode::StringLengthNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringLengthNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "原始字符串" ), stringInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "长度" ), outputPort, outputVarPtr );
		*outputVarPtr = -1;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringLengthNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringLengthNode::readyNodeRunData( ) {
	return true;
}
bool StringLengthNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
