#include "imageCreateUnityNodeEditorWidget.h"

#include <director/varDirector.h>
#include <QLineEdit>

#include "../../imageCreateUnityNode.h"
#include "imageCreateUnityNodeEditorScrollArea.h"
void ImageCreateUnityNodeEditorWidget::valueChange( QImage new_value ) {
	buffValue = new_value;
}
ImageCreateUnityNodeEditorWidget::ImageCreateUnityNodeEditorWidget( ImageCreateUnityNode *create_bin_node, QImage *bind_var_ptr ) : createBinNode( create_bin_node ), bindVarPtr( bind_var_ptr ) {
	if( bind_var_ptr == nullptr )
		return;
	imageCreateUnityNodeEditorScrollArea = new ImageCreateUnityNodeEditorScrollArea( this, *bind_var_ptr );
	editorNodeInfoScrollArea = imageCreateUnityNodeEditorScrollArea;
	connect( imageCreateUnityNodeEditorScrollArea, &ImageCreateUnityNodeEditorScrollArea::editingFinished_Signal, this, &ImageCreateUnityNodeEditorWidget::valueChange );
}
ImageCreateUnityNodeEditorWidget::~ImageCreateUnityNodeEditorWidget( ) {
	if( imageCreateUnityNodeEditorScrollArea ) {
		callNodeReleaseInfoWidgetFunction( createBinNode );
		delete imageCreateUnityNodeEditorScrollArea;
		imageCreateUnityNodeEditorScrollArea = nullptr;
		editorNodeInfoScrollArea = nullptr;
	}
}
bool ImageCreateUnityNodeEditorWidget::checkNodeValid( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	return true;
}
bool ImageCreateUnityNodeEditorWidget::initNodeInfo( Node *check_node_ptr ) {
	if( check_node_ptr != createBinNode )
		return false;
	if( createBinNode == nullptr )
		return false;
	if( NodeInfoWidget::initNodeInfo( check_node_ptr ) == false )
		return false;
	buffValue = *bindVarPtr;
	imageCreateUnityNodeEditorScrollArea->setCurrentVar( buffValue );
	return true;
}
void ImageCreateUnityNodeEditorWidget::okButtonEvent( ) {
	NodeInfoWidget::okButtonEvent( );
	*bindVarPtr = buffValue;
}
