#include "./nodeRenderScrollAreasWidget.h"

#include "nodeRenderScrollAreasWidget/nodeRenderWidget.h"

NodeRenderScrollAreasWidget::NodeRenderScrollAreasWidget( QWidget *parent, Qt::WindowFlags flags ) : QScrollArea( parent ) {
	nodeRenderWidget = new NodeRenderWidget( this, flags );
	setWidget( nodeRenderWidget );
	setWidgetResizable( true );
}
NodeRenderScrollAreasWidget::~NodeRenderScrollAreasWidget( ) {
}
