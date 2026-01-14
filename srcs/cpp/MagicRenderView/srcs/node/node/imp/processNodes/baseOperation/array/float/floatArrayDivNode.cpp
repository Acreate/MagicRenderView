#include "floatArrayDivNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/floatVectorInputPort.h>
#include <node/port/outputPort/array/floatVectorOutputPort.h>
#include <node/port/inputPort/unity/floatInputPort.h>

FloatArrayDivNode::FloatArrayDivNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool FloatArrayDivNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "浮点序列" ), firstInputPort );
		Def_AppendInputPortType( tr( "浮点" ), secondInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool FloatArrayDivNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool FloatArrayDivNode::readyNodeRunData( ) {
	return true;
}
bool FloatArrayDivNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	std::vector< NodeType > *converInt;
	NodeType *secondConverPtr;
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
	if( varDirector == nullptr || varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	*outputVarPtr = *converInt;
	outputPorts = &getRefPort( secondInputPort );
	outputPortArray = outputPorts->data( );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	parentNode = outputPortArray[ 0 ]->getParentNode( );
	varDirector = parentNode->getVarDirector( );
	if( varDirector == nullptr || varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
		return true;
	if( *secondConverPtr == 0 )
		return false;
	count = outputVarPtr->size( );
	auto outputArrayPtr = outputVarPtr->data( );
	for( index = 0; index < count; index += 1 )
		outputArrayPtr[ index ] /= *secondConverPtr;
	return true;
}
