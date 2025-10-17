#include "./varSub.h"

#include "../../prot/inputProt/inpInputPort/float/floatInputPort.h"
#include "../../prot/outputProt/impOutputPort/float/floatOutputPort.h"

Imp_StaticMetaInfo( VarSub, QObject::tr( "减" ), QObject::tr( "计算" ) );

VarSub::VarSub( ) : NodeItem( ) {
}
bool VarSub::intPortItems( MainWidget *parent ) {
	return initNodeItem( parent, [this] ( MainWidget *main_widget_parent ) {
		// 初始化节点名称
		setNodeTitleName( getMetaObjectName( ) );
		addInputProt< FloatInputPort >( "被减数" );
		addInputProt< FloatInputPort >( "减数" );
		addOutputProt< FloatOutputPort >( "结果" );
		return true;
	} );
}
