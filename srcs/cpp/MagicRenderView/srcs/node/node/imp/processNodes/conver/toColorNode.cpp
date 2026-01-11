#include "toColorNode.h"

#include "../../../../../director/varDirector.h"
#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/outputPort/unity/colorOutputPort.h"
#include "../../../../port/outputPort/unity/stringOutputPort.h"

ToColorNode::ToColorNode( const QString &node_name ) : ProcessNode( node_name ) {
	outVarPtr = nullptr;
}
bool ToColorNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		anyVarInputPortPtr = appendInputPortType< AnyVarInputPort >( tr( "值" ) );
		if( anyVarInputPortPtr == nullptr )
			return false;
		colorOutputPortPtr = appendOutputPortType< ColorOutputPort >( tr( "颜色" ) );
		if( colorOutputPortPtr == nullptr )
			return false;
		if( outVarPtr )
			varDirector->release( outVarPtr );
		if( varDirector->create( outVarPtr ) == false )
			return false;
		if( setPortVar( colorOutputPortPtr, outVarPtr ) == false )
			return false;
		outVarPtr->setRgb( 0, 0, 0, 0 );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToColorNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ToColorNode::readyNodeRunData( ) {
	outVarPtr->setRgb( 0, 0, 0, 0 );
	return true;
}
bool ToColorNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

	auto outputPortsPtr = getRefPort( anyVarInputPortPtr );
	size_t count = outputPortsPtr.size( );
	if( count == 0 )
		return true;
	auto outputPortArrayPtr = outputPortsPtr.data( );
	OutputPort *outputPortPtr = outputPortArrayPtr[ 0 ];
	auto parentNodePtr = outputPortPtr->getParentNode( );
	auto varDirectorPtr = parentNodePtr->getVarDirector( );
	auto varPtr = outputPortPtr->getVarPtr( );
	auto setNumberVar = [this] ( const quint64 &number_var ) ->bool {
		outVarPtr->setRgba( qRgba64( number_var ) );
		return true;
	};

	QColor *colorPtr;
	if( varDirectorPtr->cast_ptr( varPtr, colorPtr ) ) {
		*outVarPtr = *colorPtr;
		return true;
	}

	QString *stringPtr;
	if( varDirectorPtr->cast_ptr( varPtr, stringPtr ) ) {
		*outVarPtr = *stringPtr;
		return true;
	}

	QChar *charPtr;
	if( varDirectorPtr->cast_ptr( varPtr, charPtr ) ) {
		outVarPtr->setAlpha( charPtr->unicode( ) );
		return true;
	}

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
	return false;
}
