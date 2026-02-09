#include "stringInsertSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/inputPort/unity/stringInputPort.h"
#include "../../../../../port/inputPort/unity/uIntInputPort.h"

Def_Entity_NodeTypeName_Function( StringInsertSubStringNode, Node::tr( "工具/在指定位置插入子字符串" ) );

StringInsertSubStringNode::StringInsertSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringInsertSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), stringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "插入字符串" ), insertStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "插入位置" ), insertIndexInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringInsertSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringInsertSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringInsertSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	QString *orgString, *insertString;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( stringInputPortPtr, orgString ) == false )
		return true;

	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( insertStringInputPortPtr, insertString ) == false )
		return true;
	uint64_t *insterIndex;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( insertIndexInputPortPtr, insterIndex ) == false )
		return true;
	*outputVarPtr = *orgString;
	outputVarPtr->insert( *insterIndex, *insertString );
	return true;
}
