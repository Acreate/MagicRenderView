#include "./strRemove.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrRemove, QObject::tr( "删除" ), QObject::tr( "字符" ) );

StrRemove::StrRemove( ) {
}
bool StrRemove::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< StringInputPort >( "原始字符串", false );
			addInputProt< StringInputPort >( "删除字符串", false );

			addOutputProt< StringOutputPort >( "结果" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
