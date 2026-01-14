#include "debugNodeStack.h"

#include "debugNodes/debug/debugInfoNode.h"
#include "debugNodes/debug/previewImageNode.h"

bool DebugNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "调试节点" );
	setObjectName( name );
	Def_EmaplaceBackNode( DebugInfoNode );
	Def_EmaplaceBackNode( PreviewImageNode );
	return true;
}

DebugNodeStack::DebugNodeStack( QObject *parent ) : NodeStack( parent ) {

}
