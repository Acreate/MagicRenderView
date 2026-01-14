#include "systemNodeStack.h"

#include "systemNodes/path/systemPathInfo.h"
#include "systemNodes/app/appInfoNode.h"

bool SystemNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "系统节点" );
	setObjectName( name );

	Def_EmaplaceBackNode( AppInfoNode );
	Def_EmaplaceBackNode( SystemPathInfo );
	return true;
}

SystemNodeStack::SystemNodeStack( QObject *parent ) : NodeStack( parent ) {

}
