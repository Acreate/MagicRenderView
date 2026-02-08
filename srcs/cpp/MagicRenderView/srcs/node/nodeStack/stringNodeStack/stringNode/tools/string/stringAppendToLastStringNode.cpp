#include "stringAppendToLastStringNode.h"

#include <director/varDirector.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <node/port/inputPort/unity/stringInputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( StringAppendToLastStringNode, Node::tr( "工具/字符串末尾追加子字符串" ) );

StringAppendToLastStringNode::StringAppendToLastStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringAppendToLastStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), stringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "追加字符串" ), appendLastSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		*outputVarPtr = '\0';
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringAppendToLastStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringAppendToLastStringNode::readyNodeRunData( ) {
	return true;
}
bool StringAppendToLastStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );
	QString *orgString;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( stringInputPortPtr, orgString ) == false )
		return true;
	*outputVarPtr = *orgString;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( appendLastSubStringInputPortPtr, orgString ) == false )
		return true;
	outputVarPtr->append( *orgString );
	return true;
}
