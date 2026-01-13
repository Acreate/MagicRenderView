#include "floatArraySelfMulNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/floatVectorInputPort.h>
#include <node/port/inputPort/unity/floatInputPort.h>
#include <node/port/outputPort/array/floatVectorOutputPort.h>
#include <node/port/outputPort/unity/floatOutputPort.h>

FloatArraySelfMulNode::FloatArraySelfMulNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool FloatArraySelfMulNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "浮点序列" ), firstInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ArrayNode::initEx( parent );

}
bool FloatArraySelfMulNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool FloatArraySelfMulNode::readyNodeRunData( ) {

	return true;
}
bool FloatArraySelfMulNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
		OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	NodeType *secondConverPtr;
	void *portVarPtr;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = &getRefPort( firstInputPort );
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
	}
	return true;
}
