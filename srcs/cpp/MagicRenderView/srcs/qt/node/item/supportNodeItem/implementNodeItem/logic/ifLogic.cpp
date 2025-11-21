#include "ifLogic.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( IfLogic, QObject::tr( "如果" ), QObject::tr( "逻辑" ) );

IfLogic::IfLogic( ) {
}
bool IfLogic::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			auto boolInputPort = addInputProt< BoolInputPort >( "条件", false );
			auto anyOutputPort = addOutputProt< AnyOutputPort >( "继续" );
			this->nodeItemFcuntion = [this, &boolInputPort, &anyOutputPort] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				bool isNext = false;
				if( varGenerate->conver( typeid( bool ), &isNext, boolInputPort->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				if( varGenerate->conver( anyOutputPort->getVar( ), typeid( bool ), &isNext ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
