#include "intArraySelfMulNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/intVectorInputPort.h>
#include <node/port/outputPort/array/intVectorOutputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( IntArraySelfMulNode, Node::tr( "自运算/序列/整数/乘法" ) );

IntArraySelfMulNode::IntArraySelfMulNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool IntArraySelfMulNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "整数序列" ), firstInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;

		return true;
	};
	return ProcessNode::initEx( parent );

}
bool IntArraySelfMulNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntArraySelfMulNode::readyNodeRunData( ) {
	return true;
}
bool IntArraySelfMulNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	NodeType *secondConverPtr;
	void *portVarPtr;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = nodeToolsPtr->getRefPort( firstInputPort );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	for( index = 0; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		varDirector = outputPortArray[ index ]->getVarDirector( );
		if( varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
			continue;
		*outputVarPtr *= *secondConverPtr;
		if( *outputVarPtr == 0 )
			return true;
	}
	return true;
}
