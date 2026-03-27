#include "liftNode.h"

#include <enums/nodeEnum.h>

#include <tools/nodeTools.h>

#include "../../../../port/inputPort/point/pointInputPort.h"
#include "../../../../port/inputPort/toPoint/toPointInputPort.h"

Def_Entity_NodeTypeName_Function( LiftNode, Node::tr( "控制/提起" ) );

bool LiftNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeComponentControlPtr->appendInputPortType( this, tr( "提起" ), pointInputPort ) == false )
			return false;
		if( nodeComponentControlPtr->appendInputPortType( this, tr( "提起钩子" ), toPointInputPort ) == false )
			return false;
		return true;
	};
	return CallNode::initEx( parent );
}
bool LiftNode::updateLayout( ) {
	if( CallNode::updateLayout( ) == false )
		return false;
	return true;
}
bool LiftNode::readyNodeRunData( ) {
	return true;
}
bool LiftNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame, std::vector< Node * > &result_need_run_ref_node_vector ) {
	return nodeComponentControlPtr->getRefPortNodeVector( toPointInputPort, result_need_run_ref_node_vector );
}

bool LiftNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
bool LiftNode::fillOutputPortCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame, std::vector< Node * > &result_next_run_advise_node_vector ) {
	return nodeComponentControlPtr->getFilterRefPortNodeVector( toPointInputPort, result_next_run_advise_node_vector, NodeEnum::NodeType::Point );
}
