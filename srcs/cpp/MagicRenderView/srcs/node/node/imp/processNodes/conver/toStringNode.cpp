#include "toStringNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>

#include <tools/imageTools.h>

ToStringNode::ToStringNode( const QString &node_name ) : ProcessNode( node_name ) { outVarPtr = nullptr; }
bool ToStringNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		anyVarInputPortPtr = appendInputPortType< AnyVarInputPort >( tr( "值" ) );
		if( anyVarInputPortPtr == nullptr )
			return false;
		stringOutputPortPtr = appendOutputPortType< StringOutputPort >( tr( "字符串" ) );
		if( stringOutputPortPtr == nullptr )
			return false;
		if( outVarPtr )
			varDirector->release( outVarPtr );
		if( varDirector->create( outVarPtr ) == false )
			return false;
		if( setPortVar( stringOutputPortPtr, outVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToStringNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToStringNode::readyNodeRunData( ) {
	outVarPtr->clear( );
	return true;
}
bool ToStringNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

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
		uint64_t buffVar;
		uint64_t orVar = colorPtr->red( );
		buffVar = colorPtr->green( );
		orVar = orVar | buffVar << 16;
		buffVar = colorPtr->blue( );
		orVar = orVar | buffVar << 32;
		buffVar = colorPtr->alpha( );
		orVar = orVar | buffVar << 48;
		*outVarPtr = QString::number( orVar );
		return true;
	}

	QImage *image;
	if( varDirectorPtr->cast_ptr( varPtr, image ) ) {
		outVarPtr->clear( );
		ImageTools::imageToBase64( *image, *outVarPtr );
		return true;
	}

	QString *stringPtr;
	if( varDirectorPtr->cast_ptr( varPtr, stringPtr ) ) {
		*outVarPtr = *stringPtr;
		return true;
	}

	QChar *charPtr;
	if( varDirectorPtr->cast_ptr( varPtr, charPtr ) ) {
		*outVarPtr = *charPtr;
		return true;
	}
	auto setNumberVar = [this] ( const auto &number_var ) ->bool {
		*outVarPtr = QString::number( number_var );
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

	outVarPtr->clear( );
	return true;
}
