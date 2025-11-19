#include "markPoint.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( MarkPoint, QObject::tr( "点" ), QObject::tr( "坐标" ) );

MarkPoint::MarkPoint( ) {
}
bool MarkPoint::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< AnyInputPort >( "继续", false );
			addOutputProt< AnyOutputPort >( "继续" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
