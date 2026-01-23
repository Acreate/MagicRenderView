#include "dateTimeNodeStack.h"

#include "dateTimeNodes/split/splitDataTimeNode.h"

bool DateTimeNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "日期时间节点" );
	setObjectName( name );
	Def_EmaplaceBackNode( SplitDataTimeNode );
	return true;
}

DateTimeNodeStack::DateTimeNodeStack( QObject *parent ) : NodeStack( parent ) {

}
