#include "scrollNodeList.h"

#include <qt/widget/nodeList.h>
ScrollNodeList::ScrollNodeList( QWidget *parent ) : QScrollArea( parent ) {
	nodeList = new NodeList( this );
	setWidget( nodeList );
	setWidgetResizable( true );
}
