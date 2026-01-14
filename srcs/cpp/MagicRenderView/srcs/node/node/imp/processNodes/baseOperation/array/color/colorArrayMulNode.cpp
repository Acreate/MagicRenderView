#include "colorArrayMulNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/colorInputPort.h>
#include <node/port/inputPort/array/colorVectorInputPort.h>
#include <node/port/outputPort/array/colorVectorOutputPort.h>

#include <tools/imageTools.h>

ColorArrayMulNode::ColorArrayMulNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ColorArrayMulNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "颜色序列" ), firstInputPort );
		Def_AppendInputPortType( tr( "颜色" ), secondInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool ColorArrayMulNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ColorArrayMulNode::readyNodeRunData( ) {
	return true;
}
bool ColorArrayMulNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
	count = outputVarPtr->size( );
	auto outputArrayPtr = outputVarPtr->data( );

	int red = secondConverPtr->red( );
	int green = secondConverPtr->green( );
	int blue = secondConverPtr->blue( );
	int alpha = secondConverPtr->alpha( );
	for( index = 0; index < count; index += 1 )
		ImageTools::colorOperation::mul( outputArrayPtr[ index ], red, green, blue, alpha );
	return true;
}
