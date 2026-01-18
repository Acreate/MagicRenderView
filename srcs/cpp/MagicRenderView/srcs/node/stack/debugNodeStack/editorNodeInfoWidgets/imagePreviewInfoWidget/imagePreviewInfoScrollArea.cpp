#include "imagePreviewInfoScrollArea.h"

#include <app/application.h>
#include <win/mainWindow.h>

#include "../../debugNodes/view/previewImageNode.h"
#include "contentWidget/previewImageContentWidget.h"

void ImagePreviewInfoScrollArea::runToNode_Slot( Node *run_target ) {
	Application *instancePtr = Application::getInstancePtr( );
	MainWindow *mainWindow = instancePtr->getMainWindow( );
	mainWindow->runToNode( run_target );
}
ImagePreviewInfoScrollArea::ImagePreviewInfoScrollArea( NodeInfoWidget *parent ) : EditorNodeInfoScrollArea( parent ) {
	previewImageContentWidget = new PreviewImageContentWidget( this );
	setWidget( previewImageContentWidget );
	connect( previewImageContentWidget, &PreviewImageContentWidget::click_builder_target_signal, this, &ImagePreviewInfoScrollArea::runToNode_Slot );
	setWidgetResizable( false );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}
bool ImagePreviewInfoScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	if( previewImageContentWidget == nullptr || previewImageContentWidget->init( ( PreviewImageNode * ) init_node ) == false )
		return false;
	return true;
}
void ImagePreviewInfoScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}
void ImagePreviewInfoScrollArea::resizeEvent( QResizeEvent *resize_event ) {
	EditorNodeInfoScrollArea::resizeEvent( resize_event );
	auto viewport = this->viewport( );
	auto viewSize = viewport->size( );
	previewImageContentWidget->setFixedSize( viewSize );
}
