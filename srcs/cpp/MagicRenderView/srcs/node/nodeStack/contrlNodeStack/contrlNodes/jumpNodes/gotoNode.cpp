#include "gotoNode.h"

#include <enums/nodeEnum.h>

#include "../../../../nodeTools/nodeTools.h"
#include "../../../../port/inputPort/anyVar/anyVarInputPort.h"
#include "../../../../port/inputPort/point/pointInputPort.h"
#include "../../../../port/inputPort/toPoint/toPointInputPort.h"

Def_Entity_NodeTypeName_Function( GotoNode, Node::tr( "控制/跳转" ) );

bool GotoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeToolsPtr->appendInputPortType( this, tr( "跳转" ), pointInputPort ) == false )
			return false;
		if( nodeToolsPtr->appendInputPortType( this, tr( "跳到定点" ), toPointInputPort ) == false )
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
bool GotoNode::readyNodeRunData( ) {
	return true;
}
bool GotoNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector, size_t current_frame ) {
	return nodeToolsPtr->getRefPortNodeVector( pointInputPort, result_need_run_ref_node_vector );
}

bool GotoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
bool GotoNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return nodeToolsPtr->getFilterRefPortNodeVector( toPointInputPort, result_next_run_advise_node_vector, NodeEnum::NodeType::Point );
}
