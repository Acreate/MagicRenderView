#include "imageCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/charOutputPort.h>

ImageCreateUnityNode::ImageCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ImageCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		*outputVarPtr = QImage( );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ImageCreateUnityNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ImageCreateUnityNode::readyNodeRunData( ) {
	return true;
}
bool ImageCreateUnityNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
