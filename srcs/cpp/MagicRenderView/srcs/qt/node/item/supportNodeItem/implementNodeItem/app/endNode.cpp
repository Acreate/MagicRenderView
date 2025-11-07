#include "endNode.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"

Imp_StaticMetaInfo( EndNode, QObject::tr( "结束" ), QObject::tr( "软件" ) );

EndNode::EndNode( ) : EndNodeItem( ) {
}
bool EndNode::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< AnyInputPort >( "返回" );
			return true;
		} );
}
