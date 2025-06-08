#include "nodeAddAction.h"

#include <qt/tools/tools.h>

NodeAddAction::NodeAddAction( QObject *parent, const QString &function_name ): QAction( ), functionName( function_name ) {
	setParent( parent );
	setText( functionName );
}
NodeAddAction::~NodeAddAction( ) {
}
