#include "charArrayConverToStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/charOutputPort.h>

#include "../../../../../port/inputPort/array/charVectorInputPort.h"
#include "../../../../../port/outputPort/unity/stringOutputPort.h"

CharArrayConverToStringNode::CharArrayConverToStringNode( const QString &node_name ) : ProcessNode( node_name ) { outVarPtr = nullptr; }
bool CharArrayConverToStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "字符序列" ), charVectorInputPortPtr );
		Def_AppendBindVarOutputPortType( tr( "字符串" ), stringOutputPortPtr, outVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool CharArrayConverToStringNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool CharArrayConverToStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outVarPtr->clear( );
	auto outputPortsPtr = getRefPort( charVectorInputPortPtr );
	size_t count = outputPortsPtr.size( );
	if( count == 0 )
		return true;
	auto outputPortArrayPtr = outputPortsPtr.data( );
	OutputPort *outputPortPtr = outputPortArrayPtr[ 0 ];
	auto parentNodePtr = outputPortPtr->getParentNode( );
	auto varDirectorPtr = parentNodePtr->getVarDirector( );
	auto varPtr = outputPortPtr->getVarPtr( );
	std::vector< QChar > *charArrayPtr;
	if( varDirectorPtr->cast_ptr( varPtr, charArrayPtr ) == false )
		return true;
	*outVarPtr = QString( charArrayPtr->data( ), charArrayPtr->size( ) );
	return true;
}
