#include "nodeAddMenu.h"

#include "action/nodeAddAction.h"

#include <qt/tools/tools.h>

#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"

bool NodeAddMenu::_initMenu( INodeStack *node_stack ) {
	if( node_stack == nullptr )
		return false;

	QMenu *topMenu = new QMenu( this );
	addMenu( topMenu );
	QString objectName = node_stack->objectName( );
	topMenu->setTitle( objectName );
	auto pairs = node_stack->permissionNodeType( );
	for( auto &pair : pairs ) {
		auto first = pair.first;
		QString name = first.first;
		auto action = new NodeAddAction( this, name );
		topMenu->addAction( action );
	}
	return true;
}
NodeAddMenu::NodeAddMenu( QWidget *parent ) : QMenu( parent ) {
	connect( this, &QMenu::triggered, [this] ( QAction *action ) {
		auto conver = qobject_cast< NodeAddAction * >( action );
		if( conver )
			emit this->activeNodeAction( conver );
		else
			emit this->activeQAction( action );
	} );
}
NodeAddMenu::~NodeAddMenu( ) {
}
