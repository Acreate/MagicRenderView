#include "./nodeRenderScrollAreasWidget.h"

#include "nodeRenderWidget.h"

NodeRenderScrollAreasWidget::NodeRenderScrollAreasWidget( QWidget *parent, Qt::WindowFlags flags ) : QScrollArea( parent ) {
	nodeRenderWidget = new NodeRenderWidget( this, flags );
	setWidget( nodeRenderWidget );
	setWidgetResizable( true );
}
NodeRenderScrollAreasWidget::~NodeRenderScrollAreasWidget( ) {
}
