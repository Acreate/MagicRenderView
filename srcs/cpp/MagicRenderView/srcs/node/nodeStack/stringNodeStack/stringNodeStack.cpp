#include "stringNodeStack.h"

#include "stringNode/addObjToArray/char/charAddToArrayNode.h"
#include "stringNode/addObjToArray/char/charArrayAddToArrayNode.h"
#include "stringNode/addObjToArray/string/stringAddToArrayNode.h"
#include "stringNode/addObjToArray/string/stringArrayAddToArrayNode.h"
#include "stringNode/conver/char/charArrayConverToStringNode.h"
#include "stringNode/conver/char/toCharNode.h"
#include "stringNode/conver/string/stringConverToCharArrayNode.h"
#include "stringNode/conver/string/toStringNode.h"
#include "stringNode/create/char/charCreateArrayNode.h"
#include "stringNode/create/char/charCreateUnityNode.h"
#include "stringNode/create/string/stringCreateArrayNode.h"
#include "stringNode/create/string/stringCreateUnityNode.h"
#include "stringNode/tools/string/stringAppendToLastStringNode.h"
#include "stringNode/tools/string/stringArrayJoinToStringNode.h"
#include "stringNode/tools/string/stringFindIndexStartSubStringNode.h"
#include "stringNode/tools/string/stringFindSubStringNode.h"
#include "stringNode/tools/string/stringInsertSubStringNode.h"
#include "stringNode/tools/string/stringLengthNode.h"
#include "stringNode/tools/string/stringRemoveAllSubStringNode.h"
#include "stringNode/tools/string/stringRemoveSubStringNode.h"
#include "stringNode/tools/string/StringReplaceAllSubStringNode.h"
#include "stringNode/tools/string/stringReplaceSubStringNode.h"
#include "stringNode/tools/string/stringSplitStringArrayNode.h"

bool StringNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "字符串节点" );
	setObjectName( name );
	Def_EmaplaceBackNode( CharAddToArrayNode );
	Def_EmaplaceBackNode( CharArrayAddToArrayNode );
	Def_EmaplaceBackNode( ToCharNode );
	Def_EmaplaceBackNode( CharCreateArrayNode );
	Def_EmaplaceBackNode( CharCreateUnityNode );
	Def_EmaplaceBackNode( CharArrayConverToStringNode );

	Def_EmaplaceBackNode( StringAddToArrayNode );
	Def_EmaplaceBackNode( StringArrayAddToArrayNode );
	Def_EmaplaceBackNode( ToStringNode );
	Def_EmaplaceBackNode( StringCreateArrayNode );
	Def_EmaplaceBackNode( StringCreateUnityNode );
	Def_EmaplaceBackNode( StringConverToCharArrayNode );

	Def_EmaplaceBackNode( StringAppendToLastStringNode );
	Def_EmaplaceBackNode( StringFindIndexStartSubStringNode );
	Def_EmaplaceBackNode( StringFindSubStringNode );
	Def_EmaplaceBackNode( StringLengthNode );
	Def_EmaplaceBackNode( StringRemoveAllSubStringNode );
	Def_EmaplaceBackNode( StringRemoveSubStringNode );
	Def_EmaplaceBackNode( StringReplaceAllSubStringNode );
	Def_EmaplaceBackNode( StringReplaceSubStringNode );
	Def_EmaplaceBackNode( StringSplitStringArrayNode );
	Def_EmaplaceBackNode( StringArrayJoinToStringNode );
	Def_EmaplaceBackNode( StringInsertSubStringNode );

	return true;
}

StringNodeStack::StringNodeStack( QObject *parent ) : NodeStack( parent ) {

}
