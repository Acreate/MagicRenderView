#include "charCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/charVectorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( CharCreateArrayNode, Node::tr( "创建/序列/字符序列" ) );

CharCreateArrayNode::CharCreateArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool CharCreateArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool CharCreateArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool CharCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool CharCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
