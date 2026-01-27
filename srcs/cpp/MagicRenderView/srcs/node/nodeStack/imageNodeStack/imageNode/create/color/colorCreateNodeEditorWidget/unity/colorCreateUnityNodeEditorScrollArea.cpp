#include "colorCreateUnityNodeEditorScrollArea.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

ColorCreateUnityNodeEditorScrollArea::ColorCreateUnityNodeEditorScrollArea( NodeInfoWidget *parent, QColor current_var ) : EditorNodeInfoScrollArea( parent ), currentVar( current_var ) {
	mainWidget = new QWidget( this );
	setWidget( mainWidget );
	mainLayout = new QVBoxLayout( mainWidget );
}
void ColorCreateUnityNodeEditorScrollArea::releaseResource( ) {
	EditorNodeInfoScrollArea::releaseResource( );
}

bool ColorCreateUnityNodeEditorScrollArea::initNode( Node *init_node ) {
	if( EditorNodeInfoScrollArea::initNode( init_node ) == false )
		return false;
	return true;
}
ColorCreateUnityNodeEditorScrollArea::~ColorCreateUnityNodeEditorScrollArea( ) {

}
void ColorCreateUnityNodeEditorScrollArea::setCurrentVar( QColor current_var ) {
	currentVar = current_var;

}
