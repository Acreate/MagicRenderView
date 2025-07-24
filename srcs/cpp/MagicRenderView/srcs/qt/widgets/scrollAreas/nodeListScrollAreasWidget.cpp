#include "./nodeListScrollAreasWidget.h"

#include "../widgets/nodeListWidget.h"
NodeListScrollAreasWidget::NodeListScrollAreasWidget( QWidget *parent, Qt::WindowFlags flags ) : QScrollArea( parent ) {
	nodeListWidget = new NodeListWidget( this );
	setWidget( nodeListWidget );
	this->setWidgetResizable( true );
}
NodeListScrollAreasWidget::~NodeListScrollAreasWidget( ) {
}
