#include "./strInsert.h"

#include <qt/generate/varGenerate.h>

#include "../../../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/string/stringInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/string/stringOutputPort.h"

Imp_StaticMetaInfo( StrInsert, QObject::tr( "插入" ), QObject::tr( "字符" ) );

StrInsert::StrInsert( ) {
}
bool StrInsert::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			auto sourceStringPort = addInputProt< StringInputPort >( "原始字符串", false );
			auto insertIndexPort = addInputProt< UIntInputPort >( "插入位置", false );
			auto insertStringPort = addInputProt< StringInputPort >( "插入字符串", false );
			auto resultStringPort = addOutputProt< StringOutputPort >( "结果" );
			this->nodeItemFcuntion = [this, &sourceStringPort, &insertIndexPort, &insertStringPort, &resultStringPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				QString left, right;
				if( varGenerate->conver( typeid( QString ), &left, sourceStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				size_t insertIndex = 0;
				if( varGenerate->conver( typeid( size_t ), &insertIndex, insertIndexPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				if( varGenerate->conver( typeid( QString ), &right, insertStringPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				left = left.insert( index, right );
				if( varGenerate->conver( resultStringPort->getVar( ), typeid( QString ), &left ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
