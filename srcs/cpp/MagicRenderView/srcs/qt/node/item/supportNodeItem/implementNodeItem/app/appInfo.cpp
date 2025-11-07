#include "appInfo.h"

#include <qt/node/prot/outputProt/impOutputPort/string/stringOutputPort.h>

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"

Imp_StaticMetaInfo( AppInfo, QObject::tr( "软件信息" ), QObject::tr( "软件" ) );

AppInfo::AppInfo( ) : ProcessNodeItem( ) {
}
bool AppInfo::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addOutputProt< StringOutputPort >( "软件全路径名称" );
		addOutputProt< StringOutputPort >( "参数列表" );
		addInputProt< AnyInputPort >( "任意" );
		return true;
	} );
}
