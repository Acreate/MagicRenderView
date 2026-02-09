#include "stringLengthNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( StringLengthNode, Node::tr( "工具/返回字符串长度" ) );

StringLengthNode::StringLengthNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringLengthNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), stringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "长度" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringLengthNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringLengthNode::readyNodeRunData( ) {
	return true;
}
bool StringLengthNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	*outputVarPtr = -1;
	QString *orgString;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( stringInputPortPtr, orgString ) == false )
		return true;
	*outputVarPtr = orgString->length( );
	return true;
}
