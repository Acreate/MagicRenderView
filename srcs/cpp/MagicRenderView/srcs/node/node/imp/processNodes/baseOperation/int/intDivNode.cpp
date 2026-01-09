#include "intDivNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/intInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

IntDivNode::IntDivNode( const QString &node_name ) : ProcessNode( node_name ) {
	addResult = nullptr;
}
bool IntDivNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		multipleAddInputPort = appendInputPortType< IntInputPort >( tr( "整数" ) );
		if( multipleAddInputPort == nullptr )
			return false;
		outputPortType = appendOutputPortType< IntOutputPort >( tr( "和" ) );
		if( outputPortType == nullptr )
			return false;
		if( setPortMultiple( multipleAddInputPort, true ) == false )
			return false;
		if( addResult == nullptr )
			if( varDirector->create( addResult ) == false )
				return false;
		if( setPortVar( outputPortType, addResult ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool IntDivNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntDivNode::readyNodeRunData( ) {
	return true;
}
bool IntDivNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	OutputPort *const*outputPortArray;
	*addResult = 0;
	size_t count;
	size_t index = 0;
	int64_t *converInt;
	void *portVarPtr;
	Node *parentNode;
	VarDirector *varDirector;
	const std::vector< OutputPort * > &outputPorts = getRefPort( multipleAddInputPort );
	outputPortArray = outputPorts.data( );
	count = outputPorts.size( );
	for( ; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		parentNode = outputPortArray[ index ]->getParentNode( );
		varDirector = parentNode->getVarDirector( );
		if( varDirector->cast_ptr( portVarPtr, converInt ) == false )
			return false;
		*addResult += *converInt;
	}
	return true;
}
