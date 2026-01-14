#include "previewImageNode.h"

#include <app/application.h>
#include <tools/infoTool.h>

#include <node/port/inputPort/unity/imageInputPort.h>

bool PreviewImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "预览图像" ), imageInputPortPtr );
		setPortMultiple( imageInputPortPtr, true );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool PreviewImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}

bool PreviewImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	// todo : 未完成
	return true;
}
