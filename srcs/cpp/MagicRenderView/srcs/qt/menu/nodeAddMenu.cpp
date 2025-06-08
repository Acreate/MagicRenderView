#include "nodeAddMenu.h"

#include "action/nodeAddAction.h"

#include <qt/tools/tools.h>

#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"

bool NodeAddMenu::_initMenu( INodeStack *node_stack ) {
	if( node_stack == nullptr )
		return false;

	QMenu *topMenu = new QMenu( this );
	addMenu( topMenu );
	topMenu->setTitle( node_stack->objectName( ) );
	auto pairs = node_stack->permissionNodeType( );
	for( auto &pair : pairs ) {
		std_shared_ptr< IFunctionDeclaration > functionDeclaration( new UserFunctionDeclaration( pair.first.first ) );
		auto action = new NodeAddAction( this, functionDeclaration );
		topMenu->addAction( action );
	}
	return true;
}
NodeAddMenu::NodeAddMenu( QWidget *parent ) : QMenu( parent ) {
}
NodeAddMenu::~NodeAddMenu( ) {
}
