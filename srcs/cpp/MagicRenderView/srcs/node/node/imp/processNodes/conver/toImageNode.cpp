#include "toImageNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/imageOutputPort.h>

#include <tools/imageTools.h>

ToImageNode::ToImageNode( const QString &node_name ) : ProcessNode( node_name ) { outVarPtr = nullptr; }
bool ToImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		anyVarInputPortPtr = appendInputPortType< AnyVarInputPort >( tr( "值" ) );
		if( anyVarInputPortPtr == nullptr )
			return false;
		imageOutputPortPtr = appendOutputPortType< ImageOutputPort >( tr( "图像" ) );
		if( imageOutputPortPtr == nullptr )
			return false;
		if( outVarPtr )
			varDirector->release( outVarPtr );
		if( varDirector->create( outVarPtr ) == false )
			return false;
		if( setPortVar( imageOutputPortPtr, outVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToImageNode::readyNodeRunData( ) {
	*outVarPtr = QImage( );
	return true;
}
bool ToImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

	auto outputPortsPtr = getRefPort( anyVarInputPortPtr );
	size_t count = outputPortsPtr.size( );
	if( count == 0 )
		return true;
	auto outputPortArrayPtr = outputPortsPtr.data( );
	OutputPort *outputPortPtr = outputPortArrayPtr[ 0 ];
	auto parentNodePtr = outputPortPtr->getParentNode( );
	auto varDirectorPtr = parentNodePtr->getVarDirector( );
	auto varPtr = outputPortPtr->getVarPtr( );

	QColor *colorPtr;
	if( varDirectorPtr->cast_ptr( varPtr, colorPtr ) ) {
		*outVarPtr = QImage( 1, 1, QImage::Format_RGBA8888 );
		outVarPtr->fill( *colorPtr );
		return true;
	}

	QImage *image;
	if( varDirectorPtr->cast_ptr( varPtr, image ) ) {
		*outVarPtr = *image;
		return true;
	}

	QString *stringPtr;
	if( varDirectorPtr->cast_ptr( varPtr, stringPtr ) ) {
		if( ImageTools::conver::base64ToImage( *stringPtr, *outVarPtr ) == false )
			*outVarPtr = QImage( );
		return true;
	}
	auto setNumberVar = [this] ( const quint64 &number_var ) ->bool {
		*outVarPtr = QImage( 1, 1, QImage::Format_RGBA8888 );
		outVarPtr->fill( QColor( qRgba64( number_var ) ) );
		return true;
	};
	uint8_t *uint8t;
	uint16_t *uint16t;
	uint32_t *uint32t;
	uint64_t *uint64t;
	if( varDirectorPtr->cast_ptr( varPtr, uint8t ) )
		return setNumberVar( *uint8t );
	if( varDirectorPtr->cast_ptr( varPtr, uint16t ) )
		return setNumberVar( *uint16t );
	if( varDirectorPtr->cast_ptr( varPtr, uint32t ) )
		return setNumberVar( *uint32t );
	if( varDirectorPtr->cast_ptr( varPtr, uint64t ) )
		return setNumberVar( *uint64t );

	int8_t *int8t;
	int16_t *int16t;
	int32_t *int32t;
	int64_t *int64t;
	if( varDirectorPtr->cast_ptr( varPtr, int8t ) )
		return setNumberVar( *int8t );
	if( varDirectorPtr->cast_ptr( varPtr, int16t ) )
		return setNumberVar( *int16t );
	if( varDirectorPtr->cast_ptr( varPtr, int32t ) )
		return setNumberVar( *int32t );
	if( varDirectorPtr->cast_ptr( varPtr, int64t ) )
		return setNumberVar( *int64t );

	float *floatPtr;
	double *doublePtr;
	if( varDirectorPtr->cast_ptr( varPtr, floatPtr ) )
		return setNumberVar( *floatPtr );
	if( varDirectorPtr->cast_ptr( varPtr, doublePtr ) )
		return setNumberVar( *doublePtr );
	*outVarPtr = QImage( );
	return true;
}
