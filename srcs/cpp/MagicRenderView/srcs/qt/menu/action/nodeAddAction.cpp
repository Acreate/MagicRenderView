#include "nodeAddAction.h"

#include <qt/tools/tools.h>

NodeAddAction::NodeAddAction( QObject *parent, const std_shared_ptr< IFunctionDeclaration > &function_declaration ): QAction( ), functionDeclaration( function_declaration ) {
	setParent( parent );
}
NodeAddAction::~NodeAddAction( ) {
}
