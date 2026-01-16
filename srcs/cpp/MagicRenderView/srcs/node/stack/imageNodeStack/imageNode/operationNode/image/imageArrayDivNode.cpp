#include "imageArrayDivNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/imageInputPort.h>
#include <node/port/inputPort/array/imageVectorInputPort.h>
#include <node/port/outputPort/array/imageVectorOutputPort.h>

#include <tools/imageTools.h>

#include "../../../../../nodeTools/nodeTools.h"

ImageArrayDivNode::ImageArrayDivNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ImageArrayDivNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "图像序列" ), firstInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "图像" ), secondInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool ImageArrayDivNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ImageArrayDivNode::readyNodeRunData( ) {
	return true;
}
bool ImageArrayDivNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
	if( varDirector == nullptr || varDirector->cast_ptr( portVarPtr, converInt ) == false )
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
	if( varDirector == nullptr || varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
		return true;
	if( secondConverPtr->isNull( ) )
		return true;
	count = outputVarPtr->size( );
	if( count == 0 )
		return true;
	auto outputArrayPtr = outputVarPtr->data( );
	int width = secondConverPtr->width( );
	int height = secondConverPtr->height( );
	int minWidth;
	int minHeight;
	for( index = 0; index < count; index += 1 ) {
		QImage &image = outputArrayPtr[ index ];
		minWidth = image.width( );
		minHeight = image.height( );
		ImageTools::imageOperation::div( image, *secondConverPtr, minWidth > width ? width : minWidth, minHeight > height ? height : minHeight );
	}

	return true;
}
