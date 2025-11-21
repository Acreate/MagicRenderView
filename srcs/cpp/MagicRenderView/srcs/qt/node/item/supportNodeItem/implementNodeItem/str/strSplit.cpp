#include "./strSplit.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"
#include "../../../../prot/outputProt/impOutputPort/struct/anyArrayOutputPort.h"

Imp_StaticMetaInfo( StrSplit, QObject::tr( "切分" ), QObject::tr( "字符" ) );

StrSplit::StrSplit( ) {
}
bool StrSplit::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			auto sourceStringPort = addInputProt< StringInputPort >( "原始字符串", false );
			auto splitStringPort = addInputProt< StringInputPort >( "切分字符串", false );

			auto resultOutPort = addOutputProt< AnyArrayOutputPort >( "结果" );
			this->nodeItemFcuntion = [this, &resultOutPort, &splitStringPort, &sourceStringPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				QString sourceString, splitString;
				if( varGenerate->conver( typeid( QString ), &sourceString, sourceStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				if( varGenerate->conver( typeid( QString ), &splitString, splitStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;

				QStringList splate = sourceString.split( splitString );
				if( varGenerate->conver( resultOutPort->getVar( ), typeid( QStringList ), &splate ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
