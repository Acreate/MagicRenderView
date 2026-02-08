#include "stringArrayJoinToStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/stringVectorInputPort.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( StringArrayJoinToStringNode, Node::tr( "工具/拼接字符串序列" ) );

StringArrayJoinToStringNode::StringArrayJoinToStringNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringArrayJoinToStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "原始字符串" ), stringVectorInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "拼接子字符串" ), jionSubStringInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "合并字符串" ), outputPortPtr, outputVarPtr ) == false )
			return false;
		outputVarPtr->clear( );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringArrayJoinToStringNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringArrayJoinToStringNode::readyNodeRunData( ) {
	return true;
}
bool StringArrayJoinToStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {

	QString *stringArrayPtr;
	std::vector< QString > *stringList;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( stringVectorInputPortPtr, stringList ) == false )
		return true;
	size_t count = stringList->size( );
	size_t index;
	if( count < 2 ) { // 过短
		if( count == 0 )
			return true;
		*outputVarPtr = stringList->data( )[ 0 ];
		return true;
	}

	QString *joinString;
	if( nodeToolsPtr->cast_ptr_ref_first_port_var_ptr( jionSubStringInputPortPtr, joinString ) == false )
		return true;
	count -= 1;
	stringArrayPtr = stringList->data( );
	*outputVarPtr = stringArrayPtr[ 0 ];
	for( index = 0; index < count; ++index )
		*outputVarPtr += stringArrayPtr[ index ] + *joinString;
	*outputVarPtr += stringArrayPtr[ index ];
	return true;
}
