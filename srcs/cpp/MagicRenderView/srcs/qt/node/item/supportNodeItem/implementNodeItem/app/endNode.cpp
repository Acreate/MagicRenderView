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
			addInputProt< AnyInputPort >( "返回", true );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
