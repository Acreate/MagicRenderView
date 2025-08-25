#include "./nodeScriptsScrollAreasWidget.h"

#include "nodeScriptsScrollAreasWidget/nodeScriptsWidget.h"

NodeScriptsScrollAreasWidget::NodeScriptsScrollAreasWidget( QWidget *parent, Qt::WindowFlags flags ) : QScrollArea( parent ) {
	nodeScriptsWidget = new NodeScriptsWidget( this, flags );
	setWidget( nodeScriptsWidget );
	setWidgetResizable( nodeScriptsWidget );
}
NodeScriptsScrollAreasWidget::~NodeScriptsScrollAreasWidget( ) {
}
