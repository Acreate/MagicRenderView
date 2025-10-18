#include "jumpLogic.h"
#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( JumpLogic, QObject::tr( "跳" ), QObject::tr( "逻辑" ) );

JumpLogic::JumpLogic( ) : NodeItem( ) {
}
bool JumpLogic::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< BoolInputPort >( "返回条件" );
			addOutputProt< AnyOutputPort >( "继续" );
			return true;
		} );
}
