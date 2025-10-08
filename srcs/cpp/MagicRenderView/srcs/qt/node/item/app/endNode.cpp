#include "endNode.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"

Imp_StaticMetaInfo( EndNode, QObject::tr( "end" ), QObject::tr( "app" ) );

EndNode::EndNode( ) : NodeItem( ) {
}
bool EndNode::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< AnyInputPort >( "返回值" );
			return true;
		} );
}
