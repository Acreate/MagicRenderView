#include "appInfo.h"

#include <qt/node/prot/outputProt/impOutputPort/string/stringOutputPort.h>

#include "../../../../../application/application.h"

#include "../../../../../varType/I_Var.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"

Imp_StaticMetaInfo( AppInfo, QObject::tr( "软件信息" ), QObject::tr( "软件" ) );

AppInfo::AppInfo( ) : ProcessNodeItem( ) {
}
bool AppInfo::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< AnyInputPort >( "任意", false );
		auto appFilePathNamePort = addOutputProt< StringOutputPort >( "软件全路径名称" );
		auto appRunArgsPort = addOutputProt< StringOutputPort >( "参数列表" );
		this->nodeItemFcuntion = [&appFilePathNamePort, this, &appRunArgsPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
			auto appFileName = ( QString * ) appFilePathNamePort->getVar( )->getVarPtr( );
			auto appRunArgs = ( QString * ) appRunArgsPort->getVar( )->getVarPtr( );
			*appFileName = applicationInstancePtr->applicationFilePath( );
			*appRunArgs = applicationInstancePtr->arguments( ).join( " " );
			return nodeItemEnum::Node_Item_Result_Type::Finish;
		};
		return true;
	} );
}
