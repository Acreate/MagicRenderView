#include "intCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/intVectorOutputPort.h>

#include <node/nodeTools/nodeTools.h>

Def_Entity_NodeTypeName_Function( IntCreateArrayNode, Node::tr( "创建/序列/整数序列" ) );

IntCreateArrayNode::IntCreateArrayNode( const QString &node_name ) : CreateNode( node_name ) {
	outputVarPtr = nullptr;
}
bool IntCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return CreateNode::initEx( parent );
}
bool IntCreateArrayNode::updateLayout( ) {
	if( CreateNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool IntCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
