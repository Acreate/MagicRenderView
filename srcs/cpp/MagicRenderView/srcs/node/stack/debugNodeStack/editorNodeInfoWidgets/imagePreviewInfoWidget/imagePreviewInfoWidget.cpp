#include "imagePreviewInfoWidget.h"

#include "../../debugNodes/view/previewImageNode.h"
#include "contentWidget/outImagePortItemScrollArea/imageOutPortItemScrollWidget.h"
#include "contentWidget/previewImageContentWidget.h"
#include "imagePreviewInfoScrollArea.h"

ImagePreviewInfoWidget::ImagePreviewInfoWidget( PreviewImageNode *debug_info_node ) : NodeInfoWidget( ), previewImageNode( debug_info_node ) {
	editorNodeInfoScrollArea = previewNodeEditorScrallArea = new ImagePreviewInfoScrollArea( this );
	auto previewImageContentWidget = previewNodeEditorScrallArea->getPreviewImageContentWidget( );
	imageOutPortItemScrollWidget = previewImageContentWidget->getImageOutPortItemScrollWidget( );
}
ImagePreviewInfoWidget::~ImagePreviewInfoWidget( ) {
	if( previewNodeEditorScrallArea ) {
		auto currentNode = previewNodeEditorScrallArea->getCurrentNode( );
		callNodeReleaseInfoWidgetFunction( currentNode );
		if( currentNode != previewImageNode )
			callNodeReleaseInfoWidgetFunction( previewImageNode );
		delete previewNodeEditorScrallArea;
		previewNodeEditorScrallArea = nullptr;
		editorNodeInfoScrollArea = nullptr;
	}
}
bool ImagePreviewInfoWidget::appendPortInfoMsg( OutputPort *output_port_ptr, const QImage &image_ref_obj ) {
	return imageOutPortItemScrollWidget->appendOutputItem( output_port_ptr, image_ref_obj );
}
bool ImagePreviewInfoWidget::clear( ) {
	return imageOutPortItemScrollWidget->clear( );
}
bool ImagePreviewInfoWidget::checkNodeValid( Node *check_node_ptr ) {
	if( ( void * ) previewImageNode != ( void * ) check_node_ptr )
		return false;
	return previewImageNode != nullptr;
}
bool ImagePreviewInfoWidget::initNodeInfo( Node *check_node_ptr ) {
	if( previewImageNode == nullptr || ( void * ) previewImageNode != ( void * ) check_node_ptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( previewImageNode ) == false )
		return false;
	clear( );
	return true;
}
