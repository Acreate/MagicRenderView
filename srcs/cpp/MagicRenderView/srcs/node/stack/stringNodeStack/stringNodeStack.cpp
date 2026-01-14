#include "stringNodeStack.h"

#include "stringNode/addObjToArray/char/charAddToArrayNode.h"
#include "stringNode/addObjToArray/string/stringAddToArrayNode.h"
#include "stringNode/conver/char/toCharNode.h"
#include "stringNode/conver/string/toStringNode.h"
#include "stringNode/create/char/charCreateArrayNode.h"
#include "stringNode/create/char/charCreateUnityNode.h"
#include "stringNode/create/string/stringCreateArrayNode.h"
#include "stringNode/create/string/stringCreateUnityNode.h"

bool StringNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "字符串节点" );
	setObjectName( name );
	Def_EmaplaceBackNode( CharAddToArrayNode );
	Def_EmaplaceBackNode( ToCharNode );
	Def_EmaplaceBackNode( CharCreateArrayNode );
	Def_EmaplaceBackNode( CharCreateUnityNode );

	Def_EmaplaceBackNode( StringAddToArrayNode );
	Def_EmaplaceBackNode( ToStringNode );
	Def_EmaplaceBackNode( StringCreateArrayNode );
	Def_EmaplaceBackNode( StringCreateUnityNode );
	return true;
}

StringNodeStack::StringNodeStack( QObject *parent ) : NodeStack( parent ) {

}
