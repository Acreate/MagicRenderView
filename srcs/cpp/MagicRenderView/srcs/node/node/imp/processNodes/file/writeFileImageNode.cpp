#include "writeFileImageNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
bool WriteFileImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< StringInputPort >( tr( "路径" ) ) == nullptr )
			return false;
		if( appendInputPortType< StringInputPort >( tr( "写入内容" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool WriteFileImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool WriteFileImageNode::readyNodeRunData( ) {
	return false;
}
bool WriteFileImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
