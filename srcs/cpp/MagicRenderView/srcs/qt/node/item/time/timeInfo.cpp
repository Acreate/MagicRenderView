#include "timeInfo.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/time/timeOutputPort.h"
Imp_StaticMetaInfo( TimeInfo, QObject::tr( "软件时间信息" ), QObject::tr( "软件" ) );

TimeInfo::TimeInfo( ) : NodeItem( ) {
}
bool TimeInfo::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< AnyInputPort >( "任意" );
		addOutputProt< TimeOutputPort >( "通用起始计算时间" );
		addOutputProt< TimeOutputPort >( "运行时间" );
		addOutputProt< TimeOutputPort >( "当前时间" );
		addOutputProt< UIntOutputPort >( "当前帧数" );
		return true;
	} );
}
