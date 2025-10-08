#include "networkInfo.h"

#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
Imp_StaticMetaInfo( NetworkInfo, QObject::tr( "NetworkInfo" ), QObject::tr( "info" ) );

NetworkInfo::NetworkInfo( ) {
}
bool NetworkInfo::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			// 初始化输入端口
			addOutputProt< StringOutputPort >( "ipv4" );
			addOutputProt< StringOutputPort >( "ipv6" );
			addOutputProt< StringOutputPort >( "域名" );
			return true;
		} );
}
