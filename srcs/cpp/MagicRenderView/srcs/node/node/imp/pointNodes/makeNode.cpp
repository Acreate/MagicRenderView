#include "makeNode.h"
#include "../../../port/outputPort/point/pointOutputPort.h"
#include "../../../port/outputPort/toPoint/toPointOutputPort.h"

bool MakeNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendOutputPortType< PointOutputPort >( tr( "定点标记" ) ) == nullptr )
			return false;
		if( appendOutputPortType< ToPointOutputPort >( tr( "跳转定点" ) ) == nullptr )
			return false;
		return true;
	};
	return PointNode::initEx( parent );
}
bool MakeNode::updateLayout( ) {
	if( PointNode::updateLayout( ) == false )
		return false;
	return true;
}
bool MakeNode::readNodeRunData( ) {
	return true;
}
bool MakeNode::fillInputPortCall( std::vector< Node * > &result_need_run_ref_node_vector ) {
	return true;
}
bool MakeNode::fillNodeCall( ) {
	return true;
}
bool MakeNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector ) {
	return true;
}
