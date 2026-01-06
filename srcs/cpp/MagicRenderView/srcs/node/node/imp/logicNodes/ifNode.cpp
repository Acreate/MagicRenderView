#include "ifNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"
#include "../../../port/inputPort/point/pointInputPort.h"
#include "../../../port/outputPort/interface/interFaceOutputPort.h"
bool IfNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< PointInputPort >( tr( "定位" ) ) == nullptr )
			return false;
		if( appendInputPortType< InterFaceInputPort >( tr( "判断" ) ) == nullptr )
			return false;
		if( appendOutputPortType< InterFaceOutputPort >( tr( "成立" ) ) == nullptr )
			return false;
		if( appendOutputPortType< InterFaceOutputPort >( tr( "失败" ) ) == nullptr )
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
bool IfNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector<Node *> &result_need_run_ref_node_vector ) {
	return true;
}
bool IfNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
bool IfNode::fillOutputPortCall( std::vector<Node *> &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
