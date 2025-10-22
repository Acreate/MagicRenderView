#include "timeDataInfo.h"

#include "../../prot/inputProt/inpInputPort/time/timeInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/time/timeOutputPort.h"
Imp_StaticMetaInfo( TimeDataInfo, QObject::tr( "系统时间信息" ), QObject::tr( "软件" ) );

TimeDataInfo::TimeDataInfo( ) : NodeItem( ) {
}
bool TimeDataInfo::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< TimeInputPort >( "时间" );
		addOutputProt< UIntOutputPort >( "年" );
		addOutputProt< UIntOutputPort >( "月" );
		addOutputProt< UIntOutputPort >( "日" );
		addOutputProt< UIntOutputPort >( "时" );
		addOutputProt< UIntOutputPort >( "分" );
		addOutputProt< UIntOutputPort >( "秒" );
		addOutputProt< UIntOutputPort >( "毫秒" );
		return true;
	} );
}
