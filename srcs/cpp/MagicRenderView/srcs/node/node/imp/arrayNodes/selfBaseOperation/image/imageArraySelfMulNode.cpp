#include "imageArraySelfMulNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/imageVectorInputPort.h>
#include <node/port/outputPort/unity/imageOutputPort.h>

ImageArraySelfMulNode::ImageArraySelfMulNode( const QString &node_name ) : ArrayNode( node_name ) {
	outputVarPtr = nullptr;
}
bool ImageArraySelfMulNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType( tr( "图像序列" ), firstInputPort ) == false )
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
bool ImageArraySelfMulNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ImageArraySelfMulNode::readyNodeRunData( ) {

	return true;
}
struct ImageDataInfo {
	QImage *ptr;
	size_t width;
	size_t height;

};
bool ImageArraySelfMulNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
	size_t maxWidth = 0;
	size_t maxHeight = 0;
	std::vector< ImageDataInfo * > imagePtrVector( count );
	auto imageDataInfoPtr = imagePtrVector.data( );
	outputPortArray = outputPorts->data( );
	for( index = 0; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		varDirector = outputPortArray[ index ]->getVarDirector( );
		if( varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
			continue;
		imageDataInfoPtr[ index ]->height = secondConverPtr->height( );
		imageDataInfoPtr[ index ]->width = secondConverPtr->width( );
		imageDataInfoPtr[ index ]->ptr = secondConverPtr;
		if( maxWidth < imageDataInfoPtr[ index ]->width )
			maxWidth = imageDataInfoPtr[ index ]->width;
		if( maxHeight < imageDataInfoPtr[ index ]->height )
			maxHeight = imageDataInfoPtr[ index ]->height;
	}
	*outputVarPtr = QImage( maxWidth, maxHeight, QImage::Format_RGBA8888 );
	outputVarPtr->fill( 0 );
	size_t indexHeight;
	size_t indexWidth;

	QColor pixel;
	QColor orgPixel;
	int r;
	int g;
	int b;
	int a;
	for( index = 0; index < count; index += 1 ) {
		secondConverPtr = imageDataInfoPtr[ index ]->ptr;
		for( indexWidth = 0; indexWidth < imageDataInfoPtr[ index ]->width; ++indexWidth )
			for( indexHeight = 0; indexHeight < imageDataInfoPtr[ index ]->height; ++indexHeight ) {
				pixel = secondConverPtr->pixelColor( indexWidth, indexHeight );
				orgPixel = outputVarPtr->pixelColor( indexWidth, indexHeight );
				r = pixel.red( ) * orgPixel.red( );
				g = pixel.green( ) * orgPixel.green( );
				b = pixel.blue( ) * orgPixel.blue( );
				a = pixel.alpha( ) * orgPixel.alpha( );
				pixel = QColor( r, g, b, a );
				outputVarPtr->setPixelColor( indexWidth, indexHeight, pixel );
			}
	}
	return true;
}
