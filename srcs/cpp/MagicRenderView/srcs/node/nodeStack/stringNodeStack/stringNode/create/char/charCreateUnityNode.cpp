#include "charCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/charOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( CharCreateUnityNode, Node::tr( "创建/单元/字符" ) );

CharCreateUnityNode::CharCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool CharCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool CharCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool CharCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool CharCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
