#include "stringNodeStack.h"

bool StringNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "字符串节点" );
	setObjectName( name );

	return true;
}

StringNodeStack::StringNodeStack( QObject *parent ) : NodeStack( parent ) {

}
