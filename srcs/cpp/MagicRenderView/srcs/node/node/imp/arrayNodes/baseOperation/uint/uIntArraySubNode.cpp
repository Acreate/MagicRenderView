#include "uIntArraySubNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/array/intVectorInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

UIntArraySubNode::UIntArraySubNode( const QString &node_name ) : ArrayNode( node_name ) {
	addResultVar = nullptr;
	
}
bool UIntArraySubNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		intVectorInputPort = appendInputPortType< IntVectorInputPort >( tr( "整数" ) );
		if( intVectorInputPort == nullptr )
			return false;
		intOutputPort = appendOutputPortType< IntOutputPort >( tr( "整数和" ) );
		if( intOutputPort == nullptr )
			return false;
		if( setPortMultiple( intVectorInputPort, true ) == false )
			return false;
		if( addResultVar )
			if( varDirector->create( addResultVar ) == false )
				return false;
		if( setPortVar( intOutputPort, addResultVar ) == false )
			return false;
		return true;
	};
	return ArrayNode::initEx( parent );
}
bool UIntArraySubNode::updateLayout( ) {
	if( ArrayNode::updateLayout( ) == false )
		return false;
	return true;
}
bool UIntArraySubNode::readyNodeRunData( ) {
	return true;
}

bool UIntArraySubNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	*addResultVar = 0;
	auto outputPorts = getRefPort( intVectorInputPort );
	size_t count = outputPorts.size( );
	auto outputPortArrayPtr = outputPorts.data( );
	size_t index = 0;
	void *outputVarPtr;
	Node *parentNode;
	VarDirector *varDirector;
	int64_t *converVar;
	for( ; index < count; index += 1 ) {
		outputVarPtr = outputPortArrayPtr[ index ]->getVarPtr( );
		parentNode = outputPortArrayPtr[ index ]->getParentNode( );
		varDirector = parentNode->getVarDirector( );
		if( varDirector->cast_ptr( outputVarPtr, converVar ) == false )
			return false;
		*addResultVar += *converVar;
	}
	return true;
}
