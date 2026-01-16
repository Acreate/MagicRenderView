#include "stringSplitStringArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <node/port/inputPort/unity/stringInputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/outputPort/array/stringVectorOutputPort.h"

StringSplitStringArrayNode::StringSplitStringArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringSplitStringArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), stringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "切分符串" ), splitSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		outputVarPtr->clear( );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringSplitStringArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringSplitStringArrayNode::readyNodeRunData( ) {
	return true;
}
bool StringSplitStringArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
