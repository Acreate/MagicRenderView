#include "previewImageNode.h"

#include <app/application.h>
#include <tools/infoTool.h>

#include <node/port/inputPort/unity/imageInputPort.h>

bool PreviewImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< >( tr( "图像" ), imageInputPortPtr ) == false )
			return false;
		setPortMultiple( imageInputPortPtr, true );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool PreviewImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool PreviewImageNode::readyNodeRunData( ) {
	return true;
}
bool PreviewImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {

	return true;
}
