#include "binArraySelfAddNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/binInputPort.h>
#include <node/port/outputPort/unity/binOutputPort.h>
#include <node/port/inputPort/array/binVectorInputPort.h>

#include <node/nodeTools/nodeTools.h>

BinArraySelfAddNode::BinArraySelfAddNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool BinArraySelfAddNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "二进制序列" ), firstInputPort );
		Def_AppendInputPortType( tr( "二进制" ), secondInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool BinArraySelfAddNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool BinArraySelfAddNode::readyNodeRunData( ) {
	return true;
}
bool BinArraySelfAddNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
		*outputVarPtr += *secondConverPtr;
	}
	return true;
}
