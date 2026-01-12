#include "floatDivNode.h"

#include <director/varDirector.h>

#include "../../../../../port/inputPort/unity/floatInputPort.h"
#include "../../../../../port/outputPort/unity/floatOutputPort.h"

FloatDivNode::FloatDivNode( const QString &node_name ) : UnityNode( node_name ) {
	outputVarPtr = nullptr;
}
bool FloatDivNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( appendInputPortType( tr( "浮点" ), firstInputPort ) == false )
			return false;
		if( appendInputPortType( tr( "浮点列表" ), secondInputPort ) == false )
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
	return UnityNode::initEx( parent );

}
bool FloatDivNode::updateLayout( ) {
	if( UnityNode::updateLayout( ) == false )
		return false;
	return true;
}
bool FloatDivNode::readyNodeRunData( ) {
	*outputVarPtr = 0;

	return true;
}
bool FloatDivNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	OutputPort *const*outputPortArray;
	size_t count;
	NodeType *converInt;
	void *portVarPtr;
	VarDirector *varDirector;
	const std::vector< OutputPort * > *outputPorts = &getRefPort( firstInputPort );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	varDirector = outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	*outputVarPtr = *converInt;
	outputPorts = &getRefPort( secondInputPort );
	count = outputPorts->size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts->data( );
	portVarPtr = outputPortArray[ 0 ]->getVarPtr( );
	varDirector = outputPortArray[ 0 ]->getVarDirector( );
	if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
		return true;
	if( *converInt == 0 ) {
		*outputVarPtr = 0;
		return true;
	}
	*outputVarPtr /= *converInt;

	return true;
}
