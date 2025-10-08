#include "foreachLogic.h"

#include "../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( ForeachLogic, QObject::tr( "foreach" ), QObject::tr( "logic" ) );

ForeachLogic::ForeachLogic( ) : NodeItem( ) {
}
bool ForeachLogic::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< BoolInputPort >( "逻辑条件" );
			addOutputProt< AnyOutputPort >( "结果" );
			return true;
		} );
}
