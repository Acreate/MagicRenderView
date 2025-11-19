#include "timeInfo.h"

#include <QDateTime>

#include "../../../../../application/application.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../../varType/I_Var.h"

#include "../../../../director/nodeDirector.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"
#include "../../../../prot/outputProt/impOutputPort/time/timeOutputPort.h"

Imp_StaticMetaInfo( TimeInfo, QObject::tr( "软件时间信息" ), QObject::tr( "软件" ) );

TimeInfo::TimeInfo( ) {
}
bool TimeInfo::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< AnyInputPort >( "任意", true );
		auto startRunTimePort = addOutputProt< TimeOutputPort >( "软件起始计算时间" );
		auto runTimeOutPort = addOutputProt< TimeOutputPort >( "节点编译计算时间" );
		auto currentTimeOutPort = addOutputProt< TimeOutputPort >( "当前时间" );
		auto currentFrameOutPort = addOutputProt< UIntOutputPort >( "当前帧数" );
		this->nodeItemFcuntion = [&startRunTimePort, this, &runTimeOutPort, &currentTimeOutPort, &currentFrameOutPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
			const QDateTime &appInstanceDateTime = applicationInstancePtr->getAppInstanceDateTime( );
			auto &rightTypeInfo = typeid( QDateTime );
			if( varGenerate->conver( startRunTimePort->getVar( ), rightTypeInfo, &appInstanceDateTime ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			const QDateTime &nodeBuilderDateTime = applicationInstancePtr->getNodeDirector( )->getBuilderDataTime( );
			if( varGenerate->conver( runTimeOutPort->getVar( ), rightTypeInfo, &nodeBuilderDateTime ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			QDateTime currentDateTime = QDateTime::currentDateTime( );
			if( varGenerate->conver( currentTimeOutPort->getVar( ), rightTypeInfo, &currentDateTime ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			uint64_t frame = ( currentDateTime - nodeBuilderDateTime ).count( );
			if( varGenerate->conver( currentFrameOutPort->getVar( ), typeid( uint64_t ), &frame ) == false )
				return nodeItemEnum::Node_Item_Result_Type::Param_Error;
			return nodeItemEnum::Node_Item_Result_Type::Finish;
		};
		return true;
	} );
}
