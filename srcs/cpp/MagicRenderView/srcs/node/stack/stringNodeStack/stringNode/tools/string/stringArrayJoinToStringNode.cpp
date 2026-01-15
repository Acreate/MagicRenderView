#include "stringArrayJoinToStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/stringVectorInputPort.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

StringArrayJoinToStringNode::StringArrayJoinToStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringArrayJoinToStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "原始字符串" ), stringVectorInputPortPtr );
		Def_AppendInputPortType( tr( "拼接子字符串" ), jionSubStringInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "合并字符串" ), outputPortPtr, outputVarPtr );
		outputVarPtr->clear( );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringArrayJoinToStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringArrayJoinToStringNode::readyNodeRunData( ) {
	return true;
}
bool StringArrayJoinToStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
