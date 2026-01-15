#include "charArrayAddToArrayNode.h"

#include <director/varDirector.h>
#include <node/port/inputPort/unity/charInputPort.h>
#include <node/port/outputPort/array/charVectorOutputPort.h>
#include <node/port/inputPort/array/charVectorInputPort.h>

CharArrayAddToArrayNode::CharArrayAddToArrayNode( const QString &node_name ) : ProcessNode( node_name ) {
	outputVarPtr = nullptr;
}
bool CharArrayAddToArrayNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "字符序列" ), firstInputPort );
		Def_AppendInputPortType( tr( "字符序列" ), secondInputPort );
		Def_AppendBindVarOutputPortType( tr( "结果" ), outputPort, outputVarPtr );
		if( setPortMultiple( secondInputPort, true ) == false )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool CharArrayAddToArrayNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool CharArrayAddToArrayNode::readyNodeRunData( ) {
	return true;
}
bool CharArrayAddToArrayNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	outputVarPtr->clear( );

	OutputPort *const*outputPortArray;
	size_t count;
	size_t index;
	std::vector< NodeType > *secondConverPtr;
	void *portVarPtr;
	VarDirector *varDirector;
	auto refPort = getRefPort( firstInputPort );
	count = refPort.size( );
	if( count == 0 )
		return true;
	auto outputPort = refPort.data( )[ 0 ];
	varDirector = outputPort->getVarDirector( );
	if( varDirector == nullptr )
		return true;
	portVarPtr = outputPort->getVarPtr( );
	std::vector< NodeType > *conver;
	if( varDirector->cast_ptr( portVarPtr, conver ) == false )
		return true;
	*outputVarPtr = *conver;

	const std::vector< OutputPort * > &outputPorts = getRefPort( secondInputPort );
	count = outputPorts.size( );
	if( count == 0 )
		return true;
	outputPortArray = outputPorts.data( );
	for( index = 0; index < count; index += 1 ) {
		portVarPtr = outputPortArray[ index ]->getVarPtr( );
		varDirector = outputPortArray[ index ]->getVarDirector( );
		if( varDirector == nullptr || varDirector->cast_ptr( portVarPtr, secondConverPtr ) == false )
			continue;
		outputVarPtr->append_range( *secondConverPtr );
	}
	return true;
}
