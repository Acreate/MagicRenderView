#include "imageCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/imageVectorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

ImageCreateArrayNode::ImageCreateArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ImageCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ImageCreateArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ImageCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool ImageCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
