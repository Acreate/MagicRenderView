#include "uIntAddToArrayNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/uIntVectorInputPort.h>
#include <node/port/inputPort/unity/uIntInputPort.h>
#include <node/port/outputPort/array/uIntVectorOutputPort.h>
#include <node/nodeTools/nodeTools.h>

Def_Entity_NodeTypeName_Function( UIntAddToArrayNode, Node::tr( "追加/无符号整数序列" ) );

UIntAddToArrayNode::UIntAddToArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool UIntAddToArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeToolsPtr->appendInputPortType( this, tr( "无符号整数序列" ), firstInputPort ) == false )
			return false;

		if( nodeToolsPtr->appendInputPortType( this, tr( "无符号整数" ), secondInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendOutputPortType( this, tr( "结果" ), outputPort, outputVarPtr ) == false )
			return false;

		if( nodeToolsPtr->setPortMultiple( secondInputPort, true ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool UIntAddToArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntAddToArrayNode::readyNodeRunData( ) {
	return true;
}
bool UIntAddToArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
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
