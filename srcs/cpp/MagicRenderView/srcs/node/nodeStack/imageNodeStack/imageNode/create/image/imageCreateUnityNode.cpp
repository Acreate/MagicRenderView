#include "imageCreateUnityNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/imageOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( ImageCreateUnityNode, Node::tr( "创建/单元/图像" ) );

ImageCreateUnityNode::ImageCreateUnityNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ImageCreateUnityNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
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
