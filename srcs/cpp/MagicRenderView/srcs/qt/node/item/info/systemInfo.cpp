#include "./systemInfo.h"

#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( SystemInfo, QObject::tr( "SystemInfo" ), QObject::tr( "info" ) );

SystemInfo::SystemInfo( )
	: NodeItem( ) {
}
bool SystemInfo::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {

			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );

			addOutputProt< StringOutputPort >( "系统全名" );
			addOutputProt< StringOutputPort >( "文件名" );
			addOutputProt< StringOutputPort >( "基本名" );
			addOutputProt< StringOutputPort >( "域名" );
			addOutputProt< StringOutputPort >( "拥有者" );
			addOutputProt< StringOutputPort >( "创建日期" );

			return true;
		} );
}
