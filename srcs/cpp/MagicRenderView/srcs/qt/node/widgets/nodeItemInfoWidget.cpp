#include "nodeItemInfoWidget.h"

#include <qmenu.h>

#include <qt/application/application.h>

#include <qt/node/director/nodeDirector.h>

NodeItemInfoWidget::NodeItemInfoWidget( NodeItem *node_item, QWidget *parent ) : QWidget( parent ), nodeItem( node_item ) {
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	nodeDirector = applicationInstancePtr->getNodeDirector( );
	nodeDirector->getNodeItemInfo( nodeItem, nodeItemInfoTarget );
}
