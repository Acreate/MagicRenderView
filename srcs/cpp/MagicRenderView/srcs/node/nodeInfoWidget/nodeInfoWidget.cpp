#include "nodeInfoWidget.h"

#include "../../win/mainWindow.h"

#include "../node/node.h"

NodeInfoWidget::NodeInfoWidget( MainWindow *parent )
	: QScrollArea( parent ) {
	hide( );
}
bool NodeInfoWidget::fitterType( Node *check_node_ptr ) const {
	return false;
}
void NodeInfoWidget::hideEvent( QHideEvent *event ) {
	QScrollArea::hideEvent( event );
}
void NodeInfoWidget::showEvent( QShowEvent *event ) {
	QScrollArea::showEvent( event );
}
