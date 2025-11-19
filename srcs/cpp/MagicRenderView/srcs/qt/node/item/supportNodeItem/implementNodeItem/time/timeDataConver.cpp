#include "timeDataConver.h"

#include <QDateTime>

#include "../../../../../generate/varGenerate.h"

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
		auto timeInputPort = addInputProt< TimeInputPort >( "时间", false );
		auto converYearOutputPort = addOutputProt< UIntOutputPort >( "间隔合计年" );
		auto converMonOutputPort = addOutputProt< UIntOutputPort >( "间隔合计月" );
		auto converDayOutputPort = addOutputProt< UIntOutputPort >( "间隔合计日" );
		auto converHourOutputPort = addOutputProt< UIntOutputPort >( "间隔合计时" );
		auto converMinuteOutputPort = addOutputProt< UIntOutputPort >( "间隔合计分" );
		auto converMecondOutputPort = addOutputProt< UIntOutputPort >( "间隔合计秒" );
		auto converMsOutputPort = addOutputProt< UIntOutputPort >( "间隔合计毫秒" );
		this->nodeItemFcuntion = [&] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
			QDateTime dateTime;
			if( varGenerate->conver( typeid( QDateTime ), &dateTime, timeInputPort->getVar( ) ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			auto &sizeTypeInfo = typeid( size_t );
			QDate orgDate;
			QDate date = dateTime.date( );
			size_t year = date.year( ); // 年
			if( varGenerate->conver( converYearOutputPort->getVar( ), sizeTypeInfo, &year ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			size_t month = date.month( ) + year * 12; // 月
			if( varGenerate->conver( converMonOutputPort->getVar( ), sizeTypeInfo, &month ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			size_t day = date.daysTo( orgDate ); // 日
			if( varGenerate->conver( converDayOutputPort->getVar( ), sizeTypeInfo, &day ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			QTime time = dateTime.time( );
			QTime orgTime;
			size_t msec = time.secsTo( orgTime ); // 毫秒
			if( varGenerate->conver( converMsOutputPort->getVar( ), sizeTypeInfo, &msec ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			size_t second = msec / 1000; // 秒
			if( varGenerate->conver( converMecondOutputPort->getVar( ), sizeTypeInfo, &second ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			size_t minute = second / 60; // 分
			if( varGenerate->conver( converMinuteOutputPort->getVar( ), sizeTypeInfo, &minute ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			size_t hour = minute / 60; // 小时
			if( varGenerate->conver( converHourOutputPort->getVar( ), sizeTypeInfo, &hour ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;

			return nodeItemEnum::Node_Item_Result_Type::Finish;
		};
		return true;
	} );
}
