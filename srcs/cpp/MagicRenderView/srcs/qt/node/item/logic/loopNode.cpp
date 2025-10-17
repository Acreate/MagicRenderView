#include "loopNode.h"

#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( LoopNode, QObject::tr( "跳" ), QObject::tr( "逻辑" ) );

LoopNode::LoopNode( ) : NodeItem( ) {
}
bool LoopNode::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< AnyInputPort >( "返回条件" );
			return true;
		} );
}
