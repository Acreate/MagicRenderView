#include "colorCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/colorVectorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( ColorCreateArrayNode, Node::tr( "创建/序列/颜色" ) );

ColorCreateArrayNode::ColorCreateArrayNode( const QString &node_name ) : CreateNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return CreateNode::initEx( parent );
}
bool ColorCreateArrayNode::updateLayout( ) {
	if( CreateNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool ColorCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
