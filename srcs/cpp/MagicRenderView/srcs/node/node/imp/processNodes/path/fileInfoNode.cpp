#include "fileInfoNode.h"

#include <app/application.h>
#include <director/printerDirector.h>
#include <node/port/inputPort/anyVar/anyVarInputPort.h>
#include <node/port/outputPort/unity/stringOutputPort.h>
#include <srack/srackInfo.h>
#include <tools/infoTool.h>

bool FileInfoNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		inputBugPort = appendInputPortType< AnyVarInputPort >( tr( "输出" ) );
		if( inputBugPort == nullptr )
			return false;
		setPortMultiple( inputBugPort, true );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool FileInfoNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool FileInfoNode::readyNodeRunData( ) {
	return true;
}
bool FileInfoNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
