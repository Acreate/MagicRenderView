#include "hookNode.h"

#include <node/port/outputPort/point/pointOutputPort.h>
#include <node/port/outputPort/toPoint/toPointOutputPort.h>

#include <tools/nodeTools.h>

Def_Entity_NodeTypeName_Function( HookNode, Node::tr( "控制/钩子位置" ) );

bool HookNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {

		if( nodeComponentControlPtr->appendOutputPortType( this, tr( "钩子标记" ), nextNode ) == false )
			return false;
		if( nodeComponentControlPtr->appendOutputPortType( this, tr( "跳转钩子" ), toPointOutputPortPtr ) == false )
			return false;
		return true;
	};
	return FunctionNode::initEx( parent );
}
bool HookNode::updateLayout( ) {
	if( FunctionNode::updateLayout( ) == false )
		return false;
	return true;
}
bool HookNode::readyNodeRunData( ) {
	return true;
}

bool HookNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
bool HookNode::fillOutputPortCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame, std::vector< Node * > &result_next_run_advise_node_vector ) {
	return nodeComponentControlPtr->getFilterNotRefPortNodeVector( nextNode, result_next_run_advise_node_vector, NodeEnum::NodeType::Point );
}
