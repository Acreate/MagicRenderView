#include "./nodeScriptsScrollAreasWidget.h"

#include "../widgets/nodeScriptsWidget.h"
NodeScriptsScrollAreasWidget::NodeScriptsScrollAreasWidget( QWidget *parent, Qt::WindowFlags flags ) : QScrollArea( parent ) {
	nodeScriptsWidget = new NodeScriptsWidget( this );
	setWidget( nodeScriptsWidget );
	setWidgetResizable( nodeScriptsWidget );
}
NodeScriptsScrollAreasWidget::~NodeScriptsScrollAreasWidget( ) {
}
