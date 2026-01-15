#include "stringRemoveSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../port/inputPort/unity/stringInputPort.h"
#include "../../../../../port/inputPort/unity/uIntInputPort.h"

StringRemoveSubStringNode::StringRemoveSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringRemoveSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		Def_AppendInputPortType( tr( "原始字符串" ), orgStringInputPortPtr );
		Def_AppendInputPortType( tr( "删除字符串" ), removeSubStringInputPortPtr );
		Def_AppendInputPortType( tr( "删除次数" ), removeCountInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringRemoveSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringRemoveSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringRemoveSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
