#include "startNode.h"

#include <QScrollArea>

#include "../../../../../widgets/generateListWidget/generateListScrollArea.h"

#include "../../../../nodeInfoWidget/startNodeInfoWidget/startNodeInfoWidget.h"

#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( StartNode, QObject::tr( "起始" ), QObject::tr( "软件" ) );

StartNode::StartNode( ) : BeginNodeItem( ) {
	nodeInfoWidget = new StartNodeInfoWidget( this );
	generateListScrollArea->setWidget( nodeInfoWidget );
	generateListScrollArea->setInit( );
}

bool StartNode::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addOutputProt< AnyOutputPort >( "运行指向" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
