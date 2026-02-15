#include "stringCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/stringVectorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( StringCreateArrayNode, Node::tr( "创建/序列/字符串序列" ) );

StringCreateArrayNode::StringCreateArrayNode( const QString &node_name ) : CreateNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return CreateNode::initEx( parent );
}
bool StringCreateArrayNode::updateLayout( ) {
	if( CreateNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool StringCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
