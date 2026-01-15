#include "stringAppendToLastStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <node/port/inputPort/unity/stringInputPort.h>

StringAppendToLastStringNode::StringAppendToLastStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringAppendToLastStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "原始字符串" ), stringInputPortPtr );
		Def_AppendInputPortType( tr( "追加字符串" ), appendLastSubStringInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringAppendToLastStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringAppendToLastStringNode::readyNodeRunData( ) {
	return true;
}
bool StringAppendToLastStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
