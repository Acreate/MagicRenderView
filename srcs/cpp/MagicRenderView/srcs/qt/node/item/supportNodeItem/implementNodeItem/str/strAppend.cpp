#include "./strAppend.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrAppend, QObject::tr( "追加" ), QObject::tr( "字符" ) );

StrAppend::StrAppend( ) {
}
bool StrAppend::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			auto firstStringInPort = addInputProt< StringInputPort >( "第一字符串", false );
			auto scondStringInPort = addInputProt< StringInputPort >( "第二字符串", false );
			auto resultOutPort = addOutputProt< StringOutputPort >( "结果" );
			this->nodeItemFcuntion = [&firstStringInPort, this, &scondStringInPort, &resultOutPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				QString left, right;
				if( varGenerate->conver( typeid( QString ), &left, firstStringInPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;

				if( varGenerate->conver( typeid( QString ), &right, scondStringInPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				left += right;
				if( varGenerate->conver( resultOutPort->getVar( ), typeid( QString ), &left ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
