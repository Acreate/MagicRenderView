#include "drawNodeWidget.h"

#include "../app/application.h"

DrawNodeWidget::DrawNodeWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
}
bool DrawNodeWidget::addNode( Node *add_node ) {
	return false;
}
