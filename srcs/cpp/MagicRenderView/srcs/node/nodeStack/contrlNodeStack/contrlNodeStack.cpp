#include "contrlNodeStack.h"

#include "contrlNodes/jumpNodes/gotoNode.h"
#include "contrlNodes/logicNodes/ifNode.h"
#include "contrlNodes/pointNodes/makeNode.h"

#define Def_EmaplaceBackNode( _Type) appendNodeGenerateUnity( _Type::getStaticNodeTypeName( ), [](const QString& node_name) { return new _Type( node_name ); }  )
bool ContrlNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "控制节点" );
	setObjectName( name );
	// 跳转
	Def_EmaplaceBackNode( GotoNode );
	// 逻辑
	Def_EmaplaceBackNode( IfNode );
	// 标记
	Def_EmaplaceBackNode( MakeNode );
	return true;
}

ContrlNodeStack::ContrlNodeStack( QObject *parent ) : NodeStack( parent ) {

}
