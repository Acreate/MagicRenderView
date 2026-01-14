#include "ifNode.h"

#include "../../../../tools/varDirectorTools.h"
#include "../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../port/inputPort/point/pointInputPort.h"
#include "../../../port/outputPort/anyVar/anyVarOutputPort.h"
bool IfNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "判断" ), ifResultPort );
		Def_AppendInputPortType( tr( "成立传递" ), trueInputPort );
		Def_AppendInputPortType( tr( "失败传递" ), falseInputPort );
		Def_AppendInputPortType( tr( "定位" ), pointInputPort );
		Def_AppendOutputPortType( tr( "成立" ), trueOutputPort );
		Def_AppendOutputPortType( tr( "失败" ), falseOutputPort );
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
bool IfNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) {
	bool resultBool = getRefPortNodeVector( ifResultPort, result_need_run_ref_node_vector );
	return resultBool;
}
bool IfNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

	auto &outputPorts = getRefPort( ifResultPort );
	size_t count = outputPorts.size( );
	if( count == 0 ) {
		adviseNextVector.clear( );
		return true;
	}
	OutputPort *outputPort = outputPorts.data( )[ 0 ];
	auto varDirector = outputPort->getVarDirector( );
	auto varPtr = outputPort->getVarPtr( );
	if( VarDirectorTools::isTrue( varDirector, varPtr ) ) {
		varDirector = trueInputPort->getVarDirector( );
		varPtr = trueInputPort->getVarPtr( );
		getRefPortNodeVector( trueOutputPort, adviseNextVector );
		setInfo( trueOutputPort, varDirector, varPtr );
	} else {
		varDirector = falseInputPort->getVarDirector( );
		varPtr = falseInputPort->getVarPtr( );
		getRefPortNodeVector( falseOutputPort, adviseNextVector );
		setInfo( falseOutputPort, varDirector, varPtr );
	}
	return true;
}
bool IfNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) {
	result_next_run_advise_node_vector = adviseNextVector;
	return true;
}
