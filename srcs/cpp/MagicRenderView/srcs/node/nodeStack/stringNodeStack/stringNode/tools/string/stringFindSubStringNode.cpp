#include "stringFindSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( StringFindSubStringNode, Node::tr( "工具/在起始位置开始查找子字符串" ) );

StringFindSubStringNode::StringFindSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringFindSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), stringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "查找字符串" ), findTargetSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "位置" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = -1;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringFindSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringFindSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringFindSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	QString *orgString;
	*outputVarPtr = -1;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( stringInputPortPtr, orgString ) == false )
		return true;
	QString *findString;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( findTargetSubStringInputPortPtr, findString ) == false )
		return true;
	*outputVarPtr = orgString->indexOf( *findString );
	return true;
}
