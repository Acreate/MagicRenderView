#include "charCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/charOutputPort.h>

CharCreateUnityNode::CharCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool CharCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
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
bool CharCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	*outputVarPtr = '\0';
	return true;
}
