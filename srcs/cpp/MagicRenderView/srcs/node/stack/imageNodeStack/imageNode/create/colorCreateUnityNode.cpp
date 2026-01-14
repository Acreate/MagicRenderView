#include "colorCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

ColorCreateUnityNode::ColorCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		*outputVarPtr = QColor( 0, 0, 0, 255 );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ColorCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool ColorCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
