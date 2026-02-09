#include "colorArraySelfMulNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/colorVectorInputPort.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include <tools/imageTools.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( ColorArraySelfMulNode, Node::tr( "自运算/颜色/乘法" ) );

ColorArraySelfMulNode::ColorArraySelfMulNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorArraySelfMulNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "颜色序列" ), firstInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool ColorArraySelfMulNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorArraySelfMulNode::readyNodeRunData( ) {

	return true;
}
bool ColorArraySelfMulNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
	outputVarPtr->setRgb( 0, 0, 0, 0 );
	outputPortArray = outputPorts->data( );
	for( index = 0; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		varDirector = outputPortArray[ index ]->getVarDirector( );
		if( varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
			continue;
		ImageTools::colorOperation::mul( *outputVarPtr, *secondConverPtr );
	}
	return true;
}
