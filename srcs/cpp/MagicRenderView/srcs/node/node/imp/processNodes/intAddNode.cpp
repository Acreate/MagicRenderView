#include "intAddNode.h"

#include "../../../port/inputPort/unity/intInputPort.h"
#include "../../../port/outputPort/unity/intOutputPort.h"
bool IntAddNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< IntInputPort >( tr( "被加数" ) ) == nullptr )
			return false;
		if( appendInputPortType< IntInputPort >( tr( "加数" ) ) == nullptr )
			return false;
		if( appendOutputPortType< IntOutputPort >( tr( "和" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );

}
bool IntAddNode::updateLayout( ) {
	if( ProcessNode::updateLayout( ) == false )
		return false;
	return true;
}
bool IntAddNode::readNodeRunData( ) {
	return true;
}
bool IntAddNode::fillInputPortCall( std::vector<Node *> &result_need_run_ref_node_vector ) {
	return true;
}
bool IntAddNode::fillNodeCall( ) {
	return true;
}
bool IntAddNode::fillOutputPortCall( std::vector<Node *> &result_next_run_advise_node_vector ) {
	return true;
}
