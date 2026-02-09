#include "colorModNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/colorInputPort.h>
#include <node/port/outputPort/unity/colorOutputPort.h>

#include <tools/imageTools.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( ColorModNode, Node::tr( "颜色/单元/求余" ) );

ColorModNode::ColorModNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorModNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "颜色" ), firstInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "颜色" ), secondInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool ColorModNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorModNode::readyNodeRunData( ) {
	return true;
}
bool ColorModNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	OutputPort *const*outputPortArray;
	size_t count;
	NodeType *converInt;
	void *portVarPtr;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = nodeToolsPtr->getRefPort( firstInputPort );
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
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	varDirector = outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	ImageTools::colorOperation::mod( *outputVarPtr, *converInt );

	return true;
}
