#include "colorArraySelfAddNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/colorVectorInputPort.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include "../../../../../../tools/imageTools.h"

ColorArraySelfAddNode::ColorArraySelfAddNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorArraySelfAddNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( appendInputPortType( tr( "浮点" ), firstInputPort ) == false )
			return false;

		if( appendOutputPortType( tr( "结果" ), outputPort ) == false )
			return false;
		if( outputVarPtr )
			varDirector->release( outputVarPtr );
		if( varDirector->create( outputVarPtr ) == false )
			return false;
		if( setPortVar( outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ArrayNode::initEx( parent );
}
bool ColorArraySelfAddNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorArraySelfAddNode::readyNodeRunData( ) {
	return true;
}
bool ColorArraySelfAddNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
		ImageTools::colorOperation::add( *outputVarPtr, *secondConverPtr );
	}
	return true;
}
