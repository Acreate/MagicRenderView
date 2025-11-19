#include "timeDataInfo.h"

#include <QDateTime>

#include "../../../../../generate/varGenerate.h"

#include "../../../../../varType/I_Var.h"

#include "../../../../prot/inputProt/inpInputPort/time/timeInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"

Imp_StaticMetaInfo( TimeDataInfo, QObject::tr( "系统时间信息" ), QObject::tr( "软件" ) );

TimeDataInfo::TimeDataInfo( ) {
}
bool TimeDataInfo::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		auto timeInputPort = addInputProt< TimeInputPort >( "时间", false );
		auto yearOutPort = addOutputProt< UIntOutputPort >( "年" );
		auto monOutPort = addOutputProt< UIntOutputPort >( "月" );
		auto dayOutPort = addOutputProt< UIntOutputPort >( "日" );
		auto hourOutPort = addOutputProt< UIntOutputPort >( "时" );
		auto minuteOutPort = addOutputProt< UIntOutputPort >( "分" );
		auto secondOutPort = addOutputProt< UIntOutputPort >( "秒" );
		auto msOutPort = addOutputProt< UIntOutputPort >( "毫秒" );
		this->nodeItemFcuntion = [&] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
			QDateTime dataTime;
			if( varGenerate->conver( typeid( QDateTime ), &dataTime, timeInputPort->getVar( ) ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			auto date = dataTime.date( );
			auto year = ( uint64_t * ) yearOutPort->getVar( )->getVarPtr( );
			*year = date.year( );
			auto mon = ( uint64_t * ) monOutPort->getVar( )->getVarPtr( );
			*mon = date.month( );
			auto day = ( uint64_t * ) dayOutPort->getVar( )->getVarPtr( );
			*day = date.day( );
			auto time = dataTime.time( );
			auto hour = ( uint64_t * ) hourOutPort->getVar( )->getVarPtr( );
			*hour = time.hour( );
			auto minute = ( uint64_t * ) minuteOutPort->getVar( )->getVarPtr( );
			*minute = time.minute( );
			auto second = ( uint64_t * ) secondOutPort->getVar( )->getVarPtr( );
			*second = time.second( );
			auto msec = ( uint64_t * ) msOutPort->getVar( )->getVarPtr( );
			*msec = time.msec( );

			return nodeItemEnum::Node_Item_Result_Type::Finish;
		};
		return true;
	} );
}
