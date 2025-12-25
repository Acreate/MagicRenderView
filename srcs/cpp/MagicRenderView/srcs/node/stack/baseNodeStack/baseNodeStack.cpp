#include "baseNodeStack.h"

#include <QMenu>

#include "../../../app/application.h"

#include "../../../director/printerDirector.h"

#include "../../../widget/mainWidget.h"

#include "../../../win/mainWindow.h"

#include "../../node/imp/beginNodes/startNode.h"
#include "../../node/imp/cacheNodes/intArrayAddNode.h"
#include "../../node/imp/endNodes/resultNode.h"
#include "../../node/imp/generateNodes/intGenerateNode.h"
#include "../../node/imp/jumpNodes/gotoNode.h"
#include "../../node/imp/logicNodes/ifNode.h"
#include "../../node/imp/pointNodes/makeNode.h"
#include "../../node/imp/processNodes/intAddNode.h"

#define emaplace_back_node( _Type) appendNodeGenerateUnity( _Type::nodeTypeName( ), [](const QString& node_name) { return new _Type( node_name ); }  )
bool BaseNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "基础节点" );
	setObjectName( name );
	emaplace_back_node( StartNode );
	emaplace_back_node( ResultNode );
	emaplace_back_node( IntArrayAddNode );
	emaplace_back_node( IntGenerateNode );
	emaplace_back_node( GotoNode );
	emaplace_back_node( IfNode );
	emaplace_back_node( MakeNode );
	emaplace_back_node( IntAddNode );
	return true;
}

BaseNodeStack::BaseNodeStack( QObject *parent ) : NodeStack( parent ) {

}
