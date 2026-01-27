#include "imageCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

ImageCreateUnityNodeEditorScrollArea::ImageCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, const QImage &current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );

}
void ImageCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool ImageCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
ImageCreateUnityNodeEditorScrollArea::~ImageCreateUnityNodeEditorScrollArea( ) {

}
void ImageCreateUnityNodeEditorScrollArea::setCurrentVar( const QImage &current_var ) {
	currentVar = current_var.copy( );
}
