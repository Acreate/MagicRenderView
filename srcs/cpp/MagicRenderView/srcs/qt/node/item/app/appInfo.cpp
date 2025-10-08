#include "appInfo.h"

#include "../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
Imp_StaticMetaInfo( AppInfo, QObject::tr( "AppInfo" ), QObject::tr( "app" ) );

AppInfo::AppInfo( ) : NodeItem( ) {
}
bool AppInfo::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addOutputProt< StringOutputPort >( "软件全路径名称" );
		addOutputProt< StringOutputPort >( "参数列表" );
		return true;
	} );
}
