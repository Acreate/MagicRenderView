#include "stringReplaceSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <node/port/inputPort/unity/stringInputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/inputPort/unity/uIntInputPort.h"

StringReplaceSubStringNode::StringReplaceSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringReplaceSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), orgStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "替换原始字符串" ), replaceSourceSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "替换目标字符串" ), replaceTargetSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "替换次数" ), replaceCountInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringReplaceSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringReplaceSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringReplaceSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
