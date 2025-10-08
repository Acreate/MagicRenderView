#include "timeInfo.h"

#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/time/timeOutputPort.h"
Imp_StaticMetaInfo( TimeInfo, QObject::tr( "TimeInfo" ), QObject::tr( "app" ) );

TimeInfo::TimeInfo( ) : NodeItem( ) {
}
bool TimeInfo::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addOutputProt< TimeOutputPort >( "通用起始计算时间" );
		addOutputProt< TimeOutputPort >( "运行时间" );
		addOutputProt< TimeOutputPort >( "当前时间" );
		addOutputProt< UIntOutputPort >( "帧数" );
		return true;
	} );
}
