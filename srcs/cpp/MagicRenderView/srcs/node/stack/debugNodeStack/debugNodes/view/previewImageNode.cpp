#include "previewImageNode.h"

#include <app/application.h>
#include <tools/infoTool.h>

#include <node/port/inputPort/unity/imageInputPort.h>

#include "../../../../../director/nodeInfoEditorDirector.h"
#include "../../../../nodeTools/nodeTools.h"
#include "../../../../port/outputPort/outputPort.h"
#include "../../editorNodeInfoWidgets/imagePreviewInfoWidget/imagePreviewInfoWidget.h"

PreviewImageNode::PreviewImageNode( const QString &node_name ) : ProcessNode( node_name ) { imagePreviewPtr = nullptr; }
bool PreviewImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeToolsPtr->appendInputPortType( this, tr( "预览图像" ), imageInputPortPtr ) == false )
			return false;
		nodeToolsPtr->setPortMultiple( imageInputPortPtr, true );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool PreviewImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
void PreviewImageNode::releaseDebugNodeInfoWidget_Slot( NodeInfoWidget *release_ptr ) {
	if( imagePreviewPtr != release_ptr )
		return;
	imagePreviewPtr = nullptr;
}
NodeInfoWidget * PreviewImageNode::getNodeEditorWidget( ) {
	if( imagePreviewPtr )
		return imagePreviewPtr;
	imagePreviewPtr = new ImagePreviewInfoWidget( this );
	connect( imagePreviewPtr, &ImagePreviewInfoWidget::release_signal, this, &PreviewImageNode::releaseDebugNodeInfoWidget_Slot );
	return imagePreviewPtr;
}

bool PreviewImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	NodeInfoWidget *resultNodeInfoEditorWidget;
	if( instancePtr->getNodeInfoEditorDirector( )->getNodeInfoEditorWidget( this, resultNodeInfoEditorWidget ) == false )
		return true;
	if( imagePreviewPtr != resultNodeInfoEditorWidget ) {
		resultNodeInfoEditorWidget->hide( );
		return true;
	}
	if( imagePreviewPtr->initNodeInfo( this ) == false ) {
		imagePreviewPtr->hide( );
		return true;
	}
	imagePreviewPtr->show( );

	auto outputPorts = nodeToolsPtr->getRefPort( imageInputPortPtr );
	size_t count = outputPorts->size( );
	if( count == 0 )
		return true;
	size_t index;
	QImage *imagePtr;
	auto outputPortArrayPtr = outputPorts->data( );
	OutputPort *port;
	for( index = 0; index < count; ++index ) {
		port = outputPortArrayPtr[ index ];
		if( nodeToolsPtr->cast_ptr_port_var_ptr( port, imagePtr ) == false )
			continue;
		imagePreviewPtr->appendPortInfoMsg( port, *imagePtr );
	}
	return true;
}
