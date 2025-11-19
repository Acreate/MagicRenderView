#include "timeDataConver.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/time/timeInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"

Imp_StaticMetaInfo( TimeDataConver, QObject::tr( "时间转换" ), QObject::tr( "软件" ) );

TimeDataConver::TimeDataConver( ) {
}
bool TimeDataConver::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< AnyInputPort >( "任意", true );
		addInputProt< TimeInputPort >( "时间", false );
		addOutputProt< UIntOutputPort >( "间隔合计年" );
		addOutputProt< UIntOutputPort >( "间隔合计月" );
		addOutputProt< UIntOutputPort >( "间隔合计日" );
		addOutputProt< UIntOutputPort >( "间隔合计时" );
		addOutputProt< UIntOutputPort >( "间隔合计分" );
		addOutputProt< UIntOutputPort >( "间隔合计秒" );
		addOutputProt< UIntOutputPort >( "间隔合计毫秒" );
		this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
			return nodeItemEnum::Node_Item_Result_Type::Finish;
		};
		return true;
	} );
}
