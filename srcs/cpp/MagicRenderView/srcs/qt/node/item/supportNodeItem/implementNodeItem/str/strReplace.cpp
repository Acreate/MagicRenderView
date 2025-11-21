#include "./strReplace.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrReplace, QObject::tr( "替换" ), QObject::tr( "字符" ) );

StrReplace::StrReplace( ) {
}
bool StrReplace::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			auto sourceStringPort = addInputProt< StringInputPort >( "原始字符串", false );
			auto matchStringPort = addInputProt< StringInputPort >( "匹配目标字符串", false );
			auto replaceStringPort = addInputProt< StringInputPort >( "替换目标字符串", false );

			auto resultOutPort = addOutputProt< StringOutputPort >( "结果" );
			this->nodeItemFcuntion = [this, &sourceStringPort, &matchStringPort, &replaceStringPort, &resultOutPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				QString sourceString, matchString, replaceString;
				if( varGenerate->conver( typeid( QString ), &sourceString, sourceStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				if( varGenerate->conver( typeid( QString ), &matchString, matchStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				if( varGenerate->conver( typeid( QString ), &replaceString, replaceStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				sourceString = sourceString.replace( matchString, replaceString );
				if( varGenerate->conver( resultOutPort->getVar( ), typeid( QString ), &sourceString ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
