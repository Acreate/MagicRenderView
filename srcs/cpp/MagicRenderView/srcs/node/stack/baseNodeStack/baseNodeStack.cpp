#include "baseNodeStack.h"

#include <QMenu>

#include "../../../app/application.h"

#include "../../../director/printerDirector.h"

#include "../../../widget/drawNodeWidget.h"
#include "../../../widget/mainWidget.h"

#include "../../../win/mainWindow.h"

#include "../../node/control/beginNode.h"
#include "../../node/control/endNode.h"
#include "../../node/control/jumpNode.h"
#include "../../node/control/pointNode.h"
#include "../../node/logic/ifNode.h"
#include "../../node/logic/whileNode.h"

#define emaplace_back_node( _Type) appendNodeGenerateUnity( _Type::nodeTypeName( ), [] { return new _Type( ); }  )
bool BaseNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "基础节点" );
	setObjectName( name );
	emaplace_back_node( BeginNode );
	emaplace_back_node( EndNode );
	emaplace_back_node( JumpNode );
	emaplace_back_node( PointNode );
	emaplace_back_node( IfNode );
	emaplace_back_node( WhileNode );
	return true;
}

BaseNodeStack::BaseNodeStack( VarDirector *node_var_director, QObject *parent ) : NodeStack( node_var_director, parent ) {

}
