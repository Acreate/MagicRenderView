#include "nodeAddMenu.h"

#include "action/nodeAddAction.h"

#include <qt/tools/tools.h>

#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"

bool NodeAddMenu::initMenu( INodeStack *node_stack ) {
	if( node_stack == nullptr )
		return false;

	QMenu *topMenu = new QMenu( this );
	addMenu( topMenu );
	QString stackTypeName = node_stack->getStackTypeNames( )[ 0 ];
	topMenu->setTitle( stackTypeName );
	auto pairs = node_stack->permissionNodeType( );
	for( auto &[ key,value ] : pairs )
		topMenu->addAction( new NodeAddAction( this, key ) );
	return true;
}
NodeAddMenu::NodeAddMenu( QWidget *parent ) : QMenu( parent ) {
	connect( this, &QMenu::triggered, [this] ( QAction *action ) {
		emit this->activeAction( action );
	} );
}
NodeAddMenu::~NodeAddMenu( ) {
}
