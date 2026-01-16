#include "uIntArrayModNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/uIntVectorInputPort.h>
#include <node/port/inputPort/unity/uIntInputPort.h>
#include <node/port/outputPort/array/uIntVectorOutputPort.h>

#include <tools/baseOperationTools.h>

#include "../../../../../nodeTools/nodeTools.h"
UIntArrayModNode::UIntArrayModNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool UIntArrayModNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "无符号整数序列" ), firstInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "无符号整数" ), secondInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool UIntArrayModNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntArrayModNode::readyNodeRunData( ) {
	return true;
}
bool UIntArrayModNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	std::vector< NodeType > *converInt;
	NodeType *secondConverPtr;
	void *portVarPtr;
	Node *parentNode;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = nodeToolsPtr->getRefPort( firstInputPort );
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
	outputPorts = nodeToolsPtr->getRefPort( secondInputPort );
	outputPortArray = outputPorts->data( );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	parentNode = outputPortArray[ 0 ]->getParentNode( );
	varDirector = parentNode->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
		return true;
	if( *secondConverPtr == 0 )
		return true;
	count = outputVarPtr->size( );
	auto outputArrayPtr = outputVarPtr->data( );
	for( index = 0; index < count; index += 1 )
		BaseOperationTools::mod( outputArrayPtr[ index ], *secondConverPtr );
	return true;
}
