#include "readFileImageNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
bool ReadFileImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< StringInputPort >( tr( "路径" ) ) == nullptr )
			return false;
		if( appendInputPortType< StringInputPort >( tr( "写入内容" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ReadFileImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ReadFileImageNode::readyNodeRunData( ) {
	return false;
}
bool ReadFileImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
