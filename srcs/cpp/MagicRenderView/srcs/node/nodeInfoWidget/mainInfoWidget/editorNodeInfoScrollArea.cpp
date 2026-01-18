#include "editorNodeInfoScrollArea.h"

#include "../../../app/application.h"
#include "../../../director/nodeDirector.h"
#include "../mainInfoWidget/nodeInfoWidget.h"

void EditorNodeInfoScrollArea::releaseResource( ) {
}
EditorNodeInfoScrollArea::EditorNodeInfoScrollArea( NodeInfoWidget *parent ) : QScrollArea( parent ), parentNodeInfoWidget( parent ) {
	parentVarDirector = parentNodeInfoWidget->getVarDirector( );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
	hScrollAreaBar = this->horizontalScrollBar( );
	vScrollAreaBar = this->verticalScrollBar( );
}
bool EditorNodeInfoScrollArea::initNode( Node *init_node ) {
	if( parentNodeInfoWidget == nullptr )
		return false;
	releaseResource( );
	currentNode = init_node;
	return currentNode != nullptr;
}

void EditorNodeInfoScrollArea::hideEvent( QHideEvent *event ) {
	QScrollArea::hideEvent( event );

	releaseResource( );
}
bool EditorNodeInfoScrollArea::eventFilter( QObject *event_obj_ptr, QEvent *event_type ) {
	bool eventFilter = QScrollArea::eventFilter( event_obj_ptr, event_type );
	return eventFilter;
}
