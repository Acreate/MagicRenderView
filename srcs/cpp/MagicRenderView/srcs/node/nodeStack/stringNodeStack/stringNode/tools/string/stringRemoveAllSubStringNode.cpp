#include "stringRemoveAllSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"
#include "../../../../../port/inputPort/unity/stringInputPort.h"

Def_Entity_NodeTypeName_Function( StringRemoveAllSubStringNode, Node::tr( "工具/删除所有子字符串" ) );

StringRemoveAllSubStringNode::StringRemoveAllSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringRemoveAllSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), orgStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "删除匹配" ), removeSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringRemoveAllSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringRemoveAllSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringRemoveAllSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	QString *orgString, *removeTargetString;
	qint64 length;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( orgStringInputPortPtr, orgString ) == false )
		return true;
	length = orgString->length( );
	if( length == 0 )
		return true;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( removeSubStringInputPortPtr, removeTargetString ) == false )
		return true;
	*outputVarPtr = *orgString;
	qsizetype lastIndexOf;
	length = removeTargetString->length( );
	while( length ) {
		lastIndexOf = outputVarPtr->lastIndexOf( *removeTargetString );
		if( lastIndexOf == -1 )
			break;
		outputVarPtr->remove( lastIndexOf, length );
	}
	return true;
}
