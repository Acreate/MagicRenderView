#include "gotoNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"
#include "../../../port/inputPort/point/pointInputPort.h"
#include "../../../port/inputPort/toPoint/toPointInputPort.h"

bool GotoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< PointInputPort >( tr( "跳转" ) ) == nullptr )
			return false;
		if( appendInputPortType< ToPointInputPort >( tr( "跳到定点" ) ) == nullptr )
			return false;
		return true;
	};
	return JumpNode::initEx( parent );
}
bool GotoNode::updateLayout( ) {
	if( JumpNode::updateLayout( ) == false )
		return false;
	return true;
}
bool GotoNode::readNodeRunData( ) {
	return true;
}
bool GotoNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) {
	return true;
}
bool GotoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
bool GotoNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
