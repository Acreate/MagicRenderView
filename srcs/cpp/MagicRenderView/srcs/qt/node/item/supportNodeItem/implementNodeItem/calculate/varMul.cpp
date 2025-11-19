#include "./varMul.h"

#include "../../../../prot/inputProt/inpInputPort/float/floatInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/float/floatOutputPort.h"

Imp_StaticMetaInfo( VarMul, QObject::tr( "乘" ), QObject::tr( "计算" ) );

VarMul::VarMul( ) {
}
bool VarMul::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< FloatInputPort >( "被乘数", false );
		addInputProt< FloatInputPort >( "乘数", false );
		addOutputProt< FloatOutputPort >( "结果" );
		this->nodeItemFcuntion = [] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
			return nodeItemEnum::Node_Item_Result_Type::Finish;
		};
		return true;
	} );
}
