#include "intDivNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/intInputPort.h>
#include <node/port/outputPort/unity/intOutputPort.h>

IntDivNode::IntDivNode( const QString &node_name ) : UnityNode( node_name ) {
	outputVarPtr = nullptr;
}
bool IntDivNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "整数" ), firstInputPort );
		Def_AppendInputPortType( tr( "整数" ), secondInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		return true;
	};
	return UnityNode::initEx( parent );

}
bool IntDivNode::updateLayout( ) {
	if( UnityNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntDivNode::readyNodeRunData( ) {
	return true;
}
bool IntDivNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
