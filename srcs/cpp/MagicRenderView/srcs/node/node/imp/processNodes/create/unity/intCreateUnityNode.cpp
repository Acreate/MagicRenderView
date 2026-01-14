#include "intCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/charOutputPort.h>

IntCreateUnityNode::IntCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool IntCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool IntCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool IntCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	*outputVarPtr = '\0';
	return true;
}
