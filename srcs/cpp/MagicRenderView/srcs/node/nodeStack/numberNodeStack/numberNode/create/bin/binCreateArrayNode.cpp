#include "binCreateArrayNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/array/binVectorOutputPort.h>
#include <node/nodeTools/nodeTools.h>


Def_Entity_NodeTypeName_Function( BinCreateArrayNode, Node::tr( "创建/序列/二进制序列" ) );


BinCreateArrayNode::BinCreateArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool BinCreateArrayNode::initEx( MainWidget *parent ) {

	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool BinCreateArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool BinCreateArrayNode::readyNodeRunData( ) {
	return true;
}
bool BinCreateArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	return true;
}
