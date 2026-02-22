#include "previewImageNode.h"

#include <app/application.h>
#include <define/castMacro.h>
#include <tools/infoTool.h>

#include <node/port/inputPort/unity/imageInputPort.h>

#include "../../../../../director/nodeInfoEditorDirector.h"
#include <node/nodeTools/nodeComponentControl.h>
#include "../../../../port/outputPort/outputPort.h"
#include "../../editorNodeInfoWidgets/imagePreviewInfoWidget/imagePreviewInfoWidget.h"

Def_Entity_NodeTypeName_Function( PreviewImageNode, Node::tr( "预览/图像" ) );

PreviewImageNode::PreviewImageNode( const QString &node_name ) : ProcessNode( node_name ) { imagePreviewPtr = nullptr; }
bool PreviewImageNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( nodeComponentControlPtr->appendInputPortType( this, tr( "预览图像" ), imageInputPortPtr ) == false )
			return false;
		nodeComponentControlPtr->setPortMultiple( imageInputPortPtr, true );
		return true;
	};
	return ProcessNode::initEx( parent );
}
bool PreviewImageNode::updateLayout( ) {
	return ProcessNode::updateLayout( );
}
bool PreviewImageNode::initNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	auto imagePreviewInfoWidget = qobject_cast< ImagePreviewInfoWidget * >( release_ptr );
	if( imagePreviewInfoWidget == nullptr )
		return false;
	imagePreviewPtr = imagePreviewInfoWidget;
	return true;
}
void PreviewImageNode::releaseNodeInfoWidget( NodeInfoWidget *release_ptr ) {
	if( imagePreviewPtr != release_ptr )
		return;
	imagePreviewPtr = nullptr;
}
NodeInfoWidget * PreviewImageNode::getNodeInfoWidget( ) {
	if( imagePreviewPtr )
		return imagePreviewPtr;
	return new ImagePreviewInfoWidget( this );
}

bool PreviewImageNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	NodeInfoWidget *resultNodeInfoEditorWidget;
	if( instancePtr->getNodeInfoEditorDirector( )->getNodeInfoEditorWidget( this, resultNodeInfoEditorWidget ) == false )
		return true;
	if( imagePreviewPtr == nullptr )
		QObject_Cast( imagePreviewPtr, resultNodeInfoEditorWidget );
	if( imagePreviewPtr == nullptr || imagePreviewPtr != resultNodeInfoEditorWidget ) {
		resultNodeInfoEditorWidget->hide( );
		return true;
	}
	if( imagePreviewPtr->initNodeInfo( this ) == false ) {
		imagePreviewPtr->hide( );
		return true;
	}
	imagePreviewPtr->show( );
	imagePreviewPtr->clear( );
	auto outputPorts = nodeComponentControlPtr->getRefPort( imageInputPortPtr );
	size_t count = outputPorts->size( );
	if( count == 0 )
		return true;
	size_t index;
	QImage *imagePtr;
	auto outputPortArrayPtr = outputPorts->data( );
	OutputPort *port;
	for( index = 0; index < count; ++index ) {
		port = outputPortArrayPtr[ index ];
		if( nodeComponentControlPtr->cast_ptr_port_var_ptr( port, imagePtr ) == false )
			continue;
		imagePreviewPtr->appendPortInfoMsg( port, *imagePtr );
	}
	return true;
}
