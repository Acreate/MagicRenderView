#include "floatCreateArrayNode.h"

#include <node/nodeTools/nodeTools.h>
#include <director/varDirector.h>
#include <node/port/outputPort/array/floatVectorOutputPort.h>

Def_Entity_NodeTypeName_Function( FloatCreateArrayNode, Node::tr( "创建/序列/浮点序列" ) );

FloatCreateArrayNode::FloatCreateArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool FloatCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool FloatCreateArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool FloatCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool FloatCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
