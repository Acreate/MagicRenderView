#include "startNode.h"

#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( StartNode, QObject::tr( "start" ), QObject::tr( "app" ) );

StartNode::StartNode( ) : NodeItem( ) {
}
bool StartNode::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addOutputProt< AnyOutputPort >( "运行指向" );
			return true;
		} );
}
