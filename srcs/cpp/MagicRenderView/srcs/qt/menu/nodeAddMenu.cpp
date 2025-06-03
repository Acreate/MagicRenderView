#include "nodeAddMenu.h"

#include "action/nodeAddAction.h"

#include <qt/tools/tools.h>

NodeAddMenu::NodeAddMenu( QWidget *parent ) : QMenu( parent ) {
	connect( this, &QMenu::triggered, [this] ( QAction *action ) {
		auto nodeAddAction = qobject_cast< NodeAddAction * >( action );
		if( nodeAddAction )
			emit activeNodeAction( nodeAddAction );
		else
			emit activeQAction( action );
	} );
	auto newNodeAction = new NodeAddAction( this );
	newNodeAction->setText( "newNodeAction" );
	addAction( newNodeAction );
}
NodeAddMenu::~NodeAddMenu( ) {
}
