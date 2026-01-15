#include "ifNode.h"

#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/inputPort/point/pointInputPort.h>
#include <node/port/outputPort/anyVar/anyVarOutputPort.h>

#include <tools/varDirectorTools.h>

#include "../../../../nodeTools/nodeTools.h"

bool IfNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		Def_AppendInputPortType( tr( "判断" ), ifResultPort );
		Def_AppendInputPortType( tr( "传递" ), channelInputPort );
		Def_AppendInputPortType( tr( "定位" ), pointInputPort );
		Def_AppendOutputPortType( tr( "传递" ), channelOutputPort );
		return true;
	};
	return LogicNode::initEx( parent );

}
bool IfNode::updateLayout( ) {
	if( LogicNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IfNode::readyNodeRunData( ) {
	return true;
}
bool IfNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector, size_t current_frame ) {
	bool resultBool = nodeToolsPtr->getRefPortNodeVector( ifResultPort, result_need_run_ref_node_vector );
	return resultBool;
}
bool IfNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {

	adviseNextVector.clear( );
	auto outputPorts = nodeToolsPtr->getRefPort( ifResultPort );
	size_t count = outputPorts->size( );
	if( count == 0 )
		return true;
	OutputPort *outputPort = outputPorts->data( )[ 0 ];
	auto varDirector = outputPort->getVarDirector( );
	auto varPtr = outputPort->getVarPtr( );
	if( VarDirectorTools::isTrue( varDirector, varPtr ) ) {
		outputPorts = nodeToolsPtr->getRefPort( channelInputPort );
		count = outputPorts->size( );
		if( count == 0 )
			return true;
		outputPort = outputPorts->data( )[ 0 ];
		varDirector = outputPort->getVarDirector( );
		varPtr = outputPort->getVarPtr( );
		nodeToolsPtr->getRefPortNodeVector( channelOutputPort, adviseNextVector );
		nodeToolsPtr->setInfo( channelOutputPort, varDirector, varPtr );
	}
	return true;
}
bool IfNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	result_next_run_advise_node_vector = adviseNextVector;
	return true;
}
