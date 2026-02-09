#include "stringRemoveSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/inputPort/unity/stringInputPort.h"
#include "../../../../../port/inputPort/unity/uIntInputPort.h"

Def_Entity_NodeTypeName_Function( StringRemoveSubStringNode, Node::tr( "工具/在指定位置开始删除所有子字符串" ) );

StringRemoveSubStringNode::StringRemoveSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringRemoveSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), orgStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "删除字符串" ), removeSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "删除次数" ), removeCountInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringRemoveSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringRemoveSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringRemoveSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	QString *orgString, *removeTargetString;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( orgStringInputPortPtr, orgString ) == false )
		return true;
	qint64 length;
	length = orgString->length( );
	if( length == 0 )
		return true;
	*outputVarPtr = *orgString;
	uint64_t *removeCount;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( removeCountInputPortPtr, removeCount ) == false )
		return true;
	if( *removeCount == 0 )
		return true;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( removeSubStringInputPortPtr, removeTargetString ) == false )
		return true;
	length = removeTargetString->length( );
	if( length == 0 )
		return true;
	qsizetype lastIndexOf;
	uint64_t count = *removeCount;
	while( count ) {
		lastIndexOf = outputVarPtr->lastIndexOf( *removeTargetString );
		if( lastIndexOf == -1 )
			break;
		outputVarPtr->remove( lastIndexOf, length );
		--count;
	}
	return true;
}
