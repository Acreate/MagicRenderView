#include "./strRemove.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrRemove, QObject::tr( "删除" ), QObject::tr( "字符" ) );

StrRemove::StrRemove( ) {
}
bool StrRemove::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			auto firstStringInPort = addInputProt< StringInputPort >( "原始字符串", false );
			auto scondStringInPort = addInputProt< StringInputPort >( "删除字符串", false );

			auto resultOutPort = addOutputProt< StringOutputPort >( "结果" );
			this->nodeItemFcuntion = [this, &firstStringInPort, &scondStringInPort, &resultOutPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				QString left, right;
				if( varGenerate->conver( typeid( QString ), &left, firstStringInPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				if( varGenerate->conver( typeid( QString ), &right, scondStringInPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				left = left.remove( right );
				if( varGenerate->conver( resultOutPort->getVar( ), typeid( QString ), &left ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
