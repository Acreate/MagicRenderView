#include "ifNode.h"

#include "../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../port/inputPort/interface/interFaceInputPort.h"
#include "../../../port/inputPort/point/pointInputPort.h"
#include "../../../port/outputPort/anyVar/anyVarOutputPort.h"
#include "../../../port/outputPort/interface/interFaceOutputPort.h"
bool IfNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		ifResultPort = appendInputPortType< AnyVarInputPort >( tr( "判断" ) );
		if( ifResultPort == nullptr )
			return false;
		if( appendInputPortType< PointInputPort >( tr( "定位" ) ) == nullptr )
			return false;
		trueOutputPort = appendOutputPortType< AnyVarOutputPort >( tr( "成立" ) );
		if( trueOutputPort == nullptr )
			return false;
		falseOutputPort = appendOutputPortType< AnyVarOutputPort >( tr( "失败" ) );
		if( falseOutputPort == nullptr )
			return false;

		return true;
	};
	return LogicNode::initEx( parent );

}
bool IfNode::updateLayout( ) {
	if( LogicNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IfNode::readNodeRunData( ) {
	return true;
}
bool IfNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) {
	bool resultBool = getRefPortNodeVector( ifResultPort, result_need_run_ref_node_vector );
	return resultBool;
}
bool IfNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	bool result;

	if( false )
		result = getRefPortNodeVector( trueOutputPort, adviseNextVector );
	else
		result = getRefPortNodeVector( falseOutputPort, adviseNextVector );
	if( result == false )
		return false;
	// 保存输入
	return true;
}
bool IfNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) {
	result_next_run_advise_node_vector = adviseNextVector;
	return true;
}
