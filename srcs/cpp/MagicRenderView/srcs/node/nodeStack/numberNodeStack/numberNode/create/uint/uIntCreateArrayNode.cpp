#include "uIntCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/uIntVectorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( UIntCreateArrayNode, Node::tr( "创建/序列/无符号整数序列" ) );

UIntCreateArrayNode::UIntCreateArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool UIntCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool UIntCreateArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool UIntCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
