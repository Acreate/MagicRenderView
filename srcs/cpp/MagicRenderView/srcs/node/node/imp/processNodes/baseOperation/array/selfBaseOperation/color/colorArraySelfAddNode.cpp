#include "colorArraySelfAddNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/colorVectorInputPort.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include <tools/imageTools.h>

ColorArraySelfAddNode::ColorArraySelfAddNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorArraySelfAddNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "颜色序列" ), firstInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ColorArraySelfAddNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
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
