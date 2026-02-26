#include "boolAddToArrayNode.h"

#include <director/varDirector.h>
#include <tools/nodeTools.h>

#include "../../../../../port/inputPort/array/boolVectorInputPort.h"
#include "../../../../../port/inputPort/unity/boolInputPort.h"
#include "../../../../../port/outputPort/array/boolVectorOutputPort.h"

Def_Entity_NodeTypeName_Function( BoolAddToArrayNode,  Node::tr( "追加/布尔序列" ) );
BoolAddToArrayNode::BoolAddToArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool BoolAddToArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeComponentControlPtr->appendInputPortType( this, tr( "二进制序列" ), firstInputPort ) == false )
			return false;
		if( nodeComponentControlPtr->appendInputPortType( this, tr( "二进制" ), secondInputPort ) == false )
			return false;
		if( nodeComponentControlPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;
		if( nodeComponentControlPtr->setPortMultiple( secondInputPort, true ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool BoolAddToArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool BoolAddToArrayNode::readyNodeRunData( ) {
	return true;
}
bool BoolAddToArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );

	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	NodeType *secondConverPtr;
	void *portVarPtr;
	VarDirector *varDirector;
	auto refPort = nodeComponentControlPtr->getRefPort( firstInputPort );
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

	refPort = nodeComponentControlPtr->getRefPort( secondInputPort );
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
