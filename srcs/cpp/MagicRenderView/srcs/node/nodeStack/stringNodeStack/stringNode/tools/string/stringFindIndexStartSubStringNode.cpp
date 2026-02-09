#include "stringFindIndexStartSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/inputPort/unity/intInputPort.h"
#include "../../../../../port/inputPort/unity/uIntInputPort.h"

Def_Entity_NodeTypeName_Function( StringFindIndexStartSubStringNode, Node::tr( "工具/在指定位置开始查找子字符串" ) );

StringFindIndexStartSubStringNode::StringFindIndexStartSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringFindIndexStartSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), stringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "查找字符串" ), findTargetSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "开始位置" ), findStrtIndexInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "位置" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = -1;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringFindIndexStartSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringFindIndexStartSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringFindIndexStartSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	QString *orgString;
	*outputVarPtr = -1;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( stringInputPortPtr, orgString ) == false )
		return true;
	QString *findString;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( findTargetSubStringInputPortPtr, findString ) == false )
		return true;
	uint64_t *stratIndex;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( findStrtIndexInputPortPtr, stratIndex ) == false )
		return true;
	*outputVarPtr = orgString->indexOf( *findString, *stratIndex );
	return true;
}
