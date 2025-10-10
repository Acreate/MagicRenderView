#include "nodeItemInfoScrollAreaWidget.h"

#include "nodeItemInfoWidget.h"
NodeItemInfoScrollAreaWidget::NodeItemInfoScrollAreaWidget( NodeItem *node_item, QWidget *parent ) : QScrollArea( parent ) {
	contentWdiget = new NodeItemInfoWidget( node_item, this );
	setWidget( contentWdiget );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
