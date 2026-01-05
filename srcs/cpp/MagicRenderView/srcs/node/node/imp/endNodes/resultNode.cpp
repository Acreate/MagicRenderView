#include "resultNode.h"

#include "../../../port/inputPort/interface/interFaceInputPort.h"
#include "../../../port/inputPort/toBegin/toBeginInputPort.h"

bool ResultNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< InterFaceInputPort >( tr( "过程结束" ) ) == nullptr )
			return false;
		if( appendInputPortType< ToBeginInputPort >( tr( "过程返回" ) ) == nullptr )
			return false;
		return true;
	};
	return EndNode::initEx( parent );
}
bool ResultNode::updateLayout( ) {
	if( EndNode::updateLayout( ) == false )
		return false;
	return true;
}
bool ResultNode::readNodeRunData( ) {
	return true;
}
bool ResultNode::fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) {
	return true;
}
bool ResultNode::fillNodeCall( ) {
	return true;
}
bool ResultNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) {
	return true;
}
