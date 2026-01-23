#include "stringCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( StringCreateUnityNode, Node::tr( "创建/单元/字符串" ) );

StringCreateUnityNode::StringCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool StringCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
