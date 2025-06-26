#include "nodeAddMenu.h"

#include "action/nodeAddAction.h"

#include <qt/tools/tools.h>

#include "qt/functionDeclaration/userDef/userFunctionDeclaration.h"

bool NodeAddMenu::appendNodeStackObjectPtrToMenuSubMenu( INodeStack *node_stack ) {
	if( node_stack == nullptr )
		return false;

	// 开始清理子菜单
	clearMenuActions( this );
	if( tools::vector::has( menuSeed, node_stack ) == false )
		menuSeed.emplace_back( node_stack );

	size_t count = menuSeed.size( );
	if( count == 0 )
		return false;
	auto nodeStackPtr = menuSeed.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		QMenu *topMenu = new QMenu( this );
		addMenu( topMenu );
		QString stackTypeName = nodeStackPtr[ index ]->getStackTypeNames( )[ 0 ];
		topMenu->setTitle( stackTypeName );
		auto pairs = nodeStackPtr[ index ]->permissionNodeType( );
		for( auto &[ key,value ] : pairs )
			topMenu->addAction( new NodeAddAction( this, key ) );
	}

	return true;
}
void NodeAddMenu::clearMenuActions( QMenu *menu ) {
	std_vector< QAction * > deleteActions;
	auto actions = menu->actions( );
	for( auto action : actions ) {
		auto castMenu = menu->menuInAction( action );
		if( castMenu ) {
			clearMenuActions( castMenu );
			delete castMenu;
			continue;
		}
		deleteActions.emplace_back( action );
	}
	for( auto action : deleteActions )
		delete action;
}
NodeAddMenu::NodeAddMenu( QWidget *parent ) : QMenu( parent ) {
	connect( this, &QMenu::triggered, [this] ( QAction *action ) {
		emit this->activeAction( action );
	} );
}
NodeAddMenu::~NodeAddMenu( ) {
}
