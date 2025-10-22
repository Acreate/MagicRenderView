#include "ifLogic.h"

#include "../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( IfLogic, QObject::tr( "如果" ), QObject::tr( "逻辑" ) );

IfLogic::IfLogic( ) : NodeItem( ) {
}
bool IfLogic::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< BoolInputPort >( "条件" );
			addOutputProt< AnyOutputPort >( "继续" );
			return true;
		} );
}
