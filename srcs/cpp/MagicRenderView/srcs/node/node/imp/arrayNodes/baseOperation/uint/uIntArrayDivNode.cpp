#include "uIntArrayDivNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/uIntVectorInputPort.h>
#include <node/port/inputPort/unity/uIntInputPort.h>
#include <node/port/outputPort/array/uIntVectorOutputPort.h>

UIntArrayDivNode::UIntArrayDivNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool UIntArrayDivNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType( tr( "整数" ), firstInputPort ) == false )
			return false;
		if( appendInputPortType( tr( "整数列表" ), secondInputPort ) == false )
			return false;
		if( appendOutputPortType( tr( "结果" ), outputPort ) == false )
			return false;
		if( outputVarPtr )
			varDirector->release( outputVarPtr );
		if( varDirector->create( outputVarPtr ) == false )
			return false;
		if( setPortVar( outputPort, outputVarPtr ) == false )
			return false;
		if( setPortMultiple( secondInputPort, true ) == false )
			return false;
		return true;
	};
	return ArrayNode::initEx( parent );

}
bool UIntArrayDivNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntArrayDivNode::readyNodeRunData( ) {
	return true;
}
bool UIntArrayDivNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	std::vector< NodeType > *converInt;
	NodeType *secondConverPtr;
	NodeType accumulativeTotal;
	void *portVarPtr;
	Node *parentNode;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = &getRefPort( firstInputPort );
	outputVarPtr->clear( );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	varDirector = outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	*outputVarPtr = *converInt;
	outputPorts = &getRefPort( secondInputPort );
	outputPortArray = outputPorts->data( );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	accumulativeTotal = 1;
	for( index = 0; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		parentNode = outputPortArray[ index ]->getParentNode( );
		varDirector = parentNode->getVarDirector( );
		if( varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
			continue;
		accumulativeTotal *= *secondConverPtr;
	}
	count = outputVarPtr->size( );
	auto outputArrayPtr = outputVarPtr->data( );
	for( index = 0; index < count; index += 1 )
		outputArrayPtr[ index ] /= accumulativeTotal;
	return true;
}
