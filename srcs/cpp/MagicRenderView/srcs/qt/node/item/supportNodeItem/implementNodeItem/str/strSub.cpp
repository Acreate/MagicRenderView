#include "./strSub.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrSub, QObject::tr( "提取" ), QObject::tr( "字符" ) );

StrSub::StrSub( ) {
}
bool StrSub::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			auto sourceStringPort = addInputProt< StringInputPort >( "原始字符串", false );
			auto startIndexStringPort = addInputProt< UIntInputPort >( "起始位置", false );
			auto midCountStringPort = addInputProt< UIntInputPort >( "字符个数", false );
			auto resultOutPort = addOutputProt< StringOutputPort >( "结果" );
			this->nodeItemFcuntion = [this, &startIndexStringPort, &sourceStringPort, &midCountStringPort, &resultOutPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				QString left;
				if( varGenerate->conver( typeid( QString ), &left, sourceStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				size_t startIndex, midCount;
				if( varGenerate->conver( typeid( size_t ), &startIndex, startIndexStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				if( varGenerate->conver( typeid( size_t ), &midCount, midCountStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				left = left.mid( startIndex, midCount );
				if( varGenerate->conver( resultOutPort->getVar( ), typeid( QString ), &left ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
