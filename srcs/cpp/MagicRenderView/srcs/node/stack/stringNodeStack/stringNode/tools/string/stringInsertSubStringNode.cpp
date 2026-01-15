#include "stringInsertSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../port/inputPort/unity/stringInputPort.h"
#include "../../../../../port/inputPort/unity/uIntInputPort.h"

StringInsertSubStringNode::StringInsertSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringInsertSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		
		Def_AppendInputPortType( tr( "原始字符串" ), stringInputPortPtr );
		Def_AppendInputPortType( tr( "插入字符串" ), insertStringInputPortPtr );
		Def_AppendInputPortType( tr( "插入位置" ), insertIndexInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringInsertSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringInsertSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringInsertSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
