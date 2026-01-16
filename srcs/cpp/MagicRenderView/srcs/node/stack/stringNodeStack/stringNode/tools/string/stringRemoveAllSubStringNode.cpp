#include "stringRemoveAllSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/inputPort/unity/stringInputPort.h"

StringRemoveAllSubStringNode::StringRemoveAllSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringRemoveAllSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), orgStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "删除匹配" ), removeSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringRemoveAllSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringRemoveAllSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringRemoveAllSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
