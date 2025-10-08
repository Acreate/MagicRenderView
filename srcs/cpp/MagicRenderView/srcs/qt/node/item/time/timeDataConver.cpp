#include "timeDataConver.h"
#include "../../prot/inputProt/inpInputPort/time/timeInputPort.h"
#include "../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../prot/outputProt/impOutputPort/time/timeOutputPort.h"
Imp_StaticMetaInfo( TimeDataConver, QObject::tr( "TimeDataConver" ), QObject::tr( "app" ) );

TimeDataConver::TimeDataConver( ) : NodeItem( ) {
}
bool TimeDataConver::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< TimeInputPort >( "时间" );
		addOutputProt< UIntOutputPort >( "间隔合计年" );
		addOutputProt< UIntOutputPort >( "间隔合计月" );
		addOutputProt< UIntOutputPort >( "间隔合计日" );
		addOutputProt< UIntOutputPort >( "间隔合计时" );
		addOutputProt< UIntOutputPort >( "间隔合计分" );
		addOutputProt< UIntOutputPort >( "间隔合计秒" );
		addOutputProt< UIntOutputPort >( "间隔合计毫秒" );
		return true;
	} );
}
