#include "scrollNodeInfo.h"

#include <qt/widget/nodeInfo.h>
ScrollNodeInfo::ScrollNodeInfo( QWidget *parent ) : QScrollArea( parent ) {
	nodeInfo = new NodeInfo( this );
	setWidget( nodeInfo );
	setWidgetResizable( true );
	hide(  );
}
