#include "nodeItemInfoScrollAreaWidget.h"

#include "nodeItemInfoWidget.h"
NodeItemInfoScrollAreaWidget::NodeItemInfoScrollAreaWidget( NodeItem *node_item, QWidget *parent ) : NodeItemInfoScrollAreaWidget( new NodeItemInfoWidget( node_item, this ), node_item, parent ) { }
NodeItemInfoScrollAreaWidget::NodeItemInfoScrollAreaWidget( NodeItemInfoWidget *content_wdiget, NodeItem *node_item, QWidget *parent ) : QScrollArea( parent ), contentWdiget( content_wdiget ), nodeItem( node_item ) {
	setWidget( contentWdiget );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
