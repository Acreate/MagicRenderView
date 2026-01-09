#include "readFileTextNode.h"

#include <node/port/inputPort/unity/stringInputPort.h>
bool ReadFileTextNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< StringInputPort >( tr( "路径" ) ) == nullptr )
			return false;
		if( appendInputPortType< StringInputPort >( tr( "写入内容" ) ) == nullptr )
			return false;
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool ReadFileTextNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool ReadFileTextNode::readyNodeRunData( ) {
	return false;
}
bool ReadFileTextNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return false;
}
