#include "./varMul.h"

#include "../../prot/inputProt/inpInputPort/float/floatInputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"

Imp_StaticMetaInfo( VarMul, QObject::tr( "乘" ), QObject::tr( "计算" ) );

VarMul::VarMul( ) : NodeItem( ) {
}
bool VarMul::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
		addInputProt< FloatInputPort >( "被乘数" );
		addInputProt< FloatInputPort >( "乘数" );
		addOutputProt< FloatOutputPort >( "结果" );
		return true;
	} );
}
