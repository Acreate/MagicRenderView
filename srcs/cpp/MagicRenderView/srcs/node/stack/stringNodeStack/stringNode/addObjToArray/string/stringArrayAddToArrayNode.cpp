#include "stringArrayAddToArrayNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/stringVectorInputPort.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/array/stringVectorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

StringArrayAddToArrayNode::StringArrayAddToArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringArrayAddToArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "字符串序列" ), firstInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "字符串序列" ), secondInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		if( nodeToolsPtr->setPortMultiple( secondInputPort, true ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringArrayAddToArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringArrayAddToArrayNode::readyNodeRunData( ) {
	return true;
}
bool StringArrayAddToArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );

	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	std::vector< NodeType > *secondConverPtr;
	void *portVarPtr;
	VarDirector *varDirector;
	auto refPort = nodeToolsPtr->getRefPort( firstInputPort );
	count = refPort->size( );
	if( count == 0 )
		return true;
	auto outputPort = refPort->data( )[ 0 ];
	varDirector = outputPort->getVarDirector( );
	if( varDirector == nullptr )
		return true;
	portVarPtr = outputPort->getVarPtr( );
	std::vector< NodeType > *conver;
	if( varDirector->cast_ptr( portVarPtr, conver ) == false )
		return true;
	*outputVarPtr = *conver;

	refPort = nodeToolsPtr->getRefPort( secondInputPort );
	count = refPort->size( );
	if( count == 0 )
		return true;
	outputPortArray = refPort->data( );
	for( index = 0; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		varDirector = outputPortArray[ index ]->getVarDirector( );
		if( varDirector == nullptr || varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
			continue;
		outputVarPtr->append_range( *secondConverPtr );
	}
	return true;
}
