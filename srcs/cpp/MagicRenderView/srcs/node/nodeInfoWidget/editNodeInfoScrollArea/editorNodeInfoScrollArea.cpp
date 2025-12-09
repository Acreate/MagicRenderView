#include "editorNodeInfoScrollArea.h"

#include "../../../app/application.h"
#include "../../../director/nodeDirector.h"
#include "../../nodeInfo/nodeRefLinkInfo.h"
#include "../mainInfoWidget/nodeInfoWidget.h"

void EditorNodeInfoScrollArea::releaseResource( ) {
}
void EditorNodeInfoScrollArea::showNodeInfoWidgetLeft( NodeRefLinkInfo *node_ref_link_info ) {
	auto nodeDirector = Application::getInstancePtr( )->getNodeDirector( );
	auto nodeInfoWidget = nodeDirector->getNodeWidgeInfo( node_ref_link_info->getCurrentNode( ) );
	if( nodeInfoWidget == nullptr )
		return;
	if( leftWidget == nodeInfoWidget )
		return;
	if( leftWidget )
		leftWidget->hide( );
	leftWidget = nodeInfoWidget;
	if( leftWidget == rightWidget )
		rightWidget->hide( );
	leftWidget->show( );
	leftWidget->installEventFilter( this );
	leftWidget->showNodeInfoWidget( WidgetEnum::ShowType::Left );
}
void EditorNodeInfoScrollArea::showNodeInfoWidgetRight( NodeRefLinkInfo *node_ref_link_info ) {
	auto nodeDirector = Application::getInstancePtr( )->getNodeDirector( );
	auto nodeInfoWidget = nodeDirector->getNodeWidgeInfo( node_ref_link_info->getCurrentNode( ) );
	if( nodeInfoWidget == nullptr )
		return;
	if( rightWidget == nodeInfoWidget )
		return;
	if( rightWidget )
		rightWidget->hide( );
	rightWidget = nodeInfoWidget;
	if( leftWidget == rightWidget )
		leftWidget->hide( );
	rightWidget->show( );
	rightWidget->installEventFilter( this );
	rightWidget->showNodeInfoWidget( WidgetEnum::ShowType::Right );
}
EditorNodeInfoScrollArea::EditorNodeInfoScrollArea( NodeInfoWidget *parent ) : QScrollArea( parent ), parent( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
}
bool EditorNodeInfoScrollArea::initNode( Node *init_node ) {
	currentNode = init_node;
	return currentNode != nullptr;
}

void EditorNodeInfoScrollArea::hideEvent( QHideEvent *event ) {
	QScrollArea::hideEvent( event );

	releaseResource( );
	if( leftWidget )
		leftWidget->hide( );
	if( rightWidget )
		rightWidget->hide( );
}
bool EditorNodeInfoScrollArea::eventFilter( QObject *event_obj_ptr, QEvent *event_type ) {
	bool eventFilter = QScrollArea::eventFilter( event_obj_ptr, event_type );
	if( event_obj_ptr == leftWidget ) {
		switch( event_type->type( ) ) {
			case QEvent::Hide :
				leftWidget->removeEventFilter( this );
				leftWidget = nullptr;
				break;

		}
		return eventFilter;
	}
	if( event_obj_ptr == rightWidget ) {
		switch( event_type->type( ) ) {
			case QEvent::Hide :
				rightWidget->removeEventFilter( this );
				rightWidget = nullptr;
				break;

		}
		return eventFilter;
	}
	return eventFilter;
}
