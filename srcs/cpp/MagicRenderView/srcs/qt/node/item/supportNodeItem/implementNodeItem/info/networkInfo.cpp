#include "networkInfo.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( NetworkInfo, QObject::tr( "网络" ), QObject::tr( "信息" ) );

NetworkInfo::NetworkInfo( ) {
}
bool NetworkInfo::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addInputProt< AnyInputPort >( "任意", true );
			addOutputProt< StringOutputPort >( "ipv4" );
			addOutputProt< StringOutputPort >( "ipv6" );
			addOutputProt< StringOutputPort >( "域名" );
			this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
