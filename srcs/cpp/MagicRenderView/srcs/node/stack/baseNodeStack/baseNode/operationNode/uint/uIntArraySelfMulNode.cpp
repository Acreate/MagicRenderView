#include "uIntArraySelfMulNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/uIntVectorInputPort.h>
#include <node/port/outputPort/unity/uIntOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

UIntArraySelfMulNode::UIntArraySelfMulNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool UIntArraySelfMulNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "无符号整数序列" ), firstInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool UIntArraySelfMulNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntArraySelfMulNode::readyNodeRunData( ) {
	return true;
}
bool UIntArraySelfMulNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	NodeType *secondConverPtr;
	void *portVarPtr;
	Node *parentNode;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = nodeToolsPtr->getRefPort( firstInputPort );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	for( index = 0; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		parentNode = outputPortArray[ index ]->getParentNode( );
		varDirector = parentNode->getVarDirector( );
		if( varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
			continue;
		*outputVarPtr *= *secondConverPtr;
		if( *outputVarPtr == 0 )
			return true;
	}

	return true;
}
