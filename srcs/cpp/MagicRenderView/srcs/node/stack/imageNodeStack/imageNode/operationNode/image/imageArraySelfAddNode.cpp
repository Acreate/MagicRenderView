#include "imageArraySelfAddNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/imageVectorInputPort.h>
#include <node/port/outputPort/unity/imageOutputPort.h>

#include <tools/imageTools.h>

#include "../../../../../nodeTools/nodeTools.h"

ImageArraySelfAddNode::ImageArraySelfAddNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ImageArraySelfAddNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "图像序列" ), firstInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ImageArraySelfAddNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ImageArraySelfAddNode::readyNodeRunData( ) {
	return true;
}
struct ImageDataInfo {
	QImage *ptr;
	size_t width;
	size_t height;

};
bool ImageArraySelfAddNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
	size_t maxWidth = 0;
	size_t maxHeight = 0;
	std::vector< ImageDataInfo > imagePtrVector( count );
	auto imageDataInfoPtr = imagePtrVector.data( );
	outputPortArray = outputPorts->data( );
	for( index = 0; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		varDirector = outputPortArray[ index ]->getVarDirector( );
		if( varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
			continue;
		imageDataInfoPtr[ index ].height = secondConverPtr->height( );
		imageDataInfoPtr[ index ].width = secondConverPtr->width( );
		imageDataInfoPtr[ index ].ptr = secondConverPtr;
		if( maxWidth < imageDataInfoPtr[ index ].width )
			maxWidth = imageDataInfoPtr[ index ].width;
		if( maxHeight < imageDataInfoPtr[ index ].height )
			maxHeight = imageDataInfoPtr[ index ].height;
	}
	*outputVarPtr = QImage( maxWidth, maxHeight, QImage::Format_RGBA8888 );
	outputVarPtr->fill( 0 );

	for( index = 0; index < count; index += 1 )
		ImageTools::imageOperation::add( *outputVarPtr, *imageDataInfoPtr[ index ].ptr, maxWidth, maxHeight );
	return true;
}
