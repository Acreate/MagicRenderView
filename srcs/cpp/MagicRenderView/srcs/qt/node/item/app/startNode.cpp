#include "startNode.h"

#include <QScrollArea>

#include "../../nodeInfoWidget/startNodeInfoWidget/startNodeInfoWidget.h"

#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( StartNode, QObject::tr( "起始" ), QObject::tr( "软件" ) );

StartNode::StartNode( ) : NodeItem( ) {

	nodeInfoWidget = new StartNodeInfoWidget( this );
	nodeInfoScrollArea = new QScrollArea( );
	nodeInfoScrollArea->setWidget( nodeInfoWidget );
	nodeInfoScrollArea->setWidgetResizable( true );
	nodeInfoScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	nodeInfoScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
QWidget * StartNode::getNodeItemWidget( ) const {
	return nodeInfoScrollArea;
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
