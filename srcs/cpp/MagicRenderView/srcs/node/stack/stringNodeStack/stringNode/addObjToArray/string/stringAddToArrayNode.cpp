#include "stringAddToArrayNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/stringVectorInputPort.h>
#include <node/port/inputPort/unity/stringInputPort.h>
#include <node/port/outputPort/array/stringVectorOutputPort.h>

#include "../../../../../nodeTools/nodeTools.h"

StringAddToArrayNode::StringAddToArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool StringAddToArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "字符串序列" ), firstInputPort );
		Def_AppendInputPortType( tr( "字符串" ), secondInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		if( nodeToolsPtr->setPortMultiple( secondInputPort, true ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool StringAddToArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool StringAddToArrayNode::readyNodeRunData( ) {
	return true;
}
bool StringAddToArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );

	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	NodeType *secondConverPtr;
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
		outputVarPtr->emplace_back( *secondConverPtr );
	}
	return true;
}
