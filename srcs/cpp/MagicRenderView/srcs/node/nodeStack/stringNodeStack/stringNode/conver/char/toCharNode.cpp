#include "toCharNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/charOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

Def_Entity_NodeTypeName_Function( ToCharNode, Node::tr( "转换/单元/字符" ) );

ToCharNode::ToCharNode( const QString &node_name ) : ProcessNode( node_name ) { outVarPtr = nullptr; }
bool ToCharNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "值" ), anyVarInputPortPtr ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "字符" ), charOutputPortPtr, outVarPtr ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ToCharNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool ToCharNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {

	*outVarPtr = ( short ) 0;
	auto outputPortsPtr = nodeToolsPtr->getRefPort( anyVarInputPortPtr );
	size_t count = outputPortsPtr->size( );
	if( count == 0 )
		return true;
	auto outputPortArrayPtr = outputPortsPtr->data( );
	OutputPort *outputPortPtr = outputPortArrayPtr[ 0 ];
	auto parentNodePtr = outputPortPtr->getParentNode( );
	auto varDirectorPtr = parentNodePtr->getVarDirector( );
	auto varPtr = outputPortPtr->getVarPtr( );
	auto setNumberVar = [this] ( const short &number_var ) ->bool {
		*outVarPtr = number_var;
		return true;
	};

	QColor *colorPtr;
	if( varDirectorPtr->cast_ptr( varPtr, colorPtr ) ) {
		uint64_t orVar = colorPtr->red( );
		*outVarPtr = ( short ) orVar;
		return true;
	}

	QString *stringPtr;
	if( varDirectorPtr->cast_ptr( varPtr, stringPtr ) ) {
		bool result = false;
		*outVarPtr = ( short ) stringPtr->toULongLong( &result );
		if( result )
			return true;
		*outVarPtr = ( short ) stringPtr->toLongLong( &result );
		if( result )
			return true;
		*outVarPtr = ( short ) stringPtr->toDouble( &result );
		if( result )
			return true;
		return true;
	}

	QChar *charPtr;
	if( varDirectorPtr->cast_ptr( varPtr, charPtr ) ) {
		*outVarPtr = charPtr->unicode( );
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
	return setNumberVar( 0 );
}
