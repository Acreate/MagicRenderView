#include "StringReplaceAllSubStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include <node/nodeTools/nodeTools.h>
#include <tools/qstringTools.h>

Def_Entity_NodeTypeName_Function( StringReplaceAllSubStringNode, Node::tr( "工具/替换所有子字符串" ) );

StringReplaceAllSubStringNode::StringReplaceAllSubStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringReplaceAllSubStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), orgStringInputPortPtr ) == false )
			return false;

		if( nodeToolsPtr->appendInputPortType( this, tr( "替换原始字符串" ), replaceSourceSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "替换目标字符串" ), replaceTargetSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringReplaceAllSubStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringReplaceAllSubStringNode::readyNodeRunData( ) {
	return true;
}
bool StringReplaceAllSubStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	QString *orgString, *replaceTargetString, *fullString;
	qsizetype stringLength;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( orgStringInputPortPtr, orgString ) == false )
		return true;
	stringLength = orgString->length( );
	if( stringLength == 0 )
		return true;
	*outputVarPtr = *orgString;

	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( replaceSourceSubStringInputPortPtr, replaceTargetString ) == false )
		return true;
	stringLength = replaceTargetString->length( );
	if( stringLength == 0 )
		return true;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( replaceTargetSubStringInputPortPtr, fullString ) == false )
		return true;
	QStringTools::replace( *orgString, *replaceTargetString, *fullString, *outputVarPtr );
	return true;
}
