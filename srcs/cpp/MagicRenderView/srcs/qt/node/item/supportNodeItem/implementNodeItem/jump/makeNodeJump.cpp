#include "makeNodeJump.h"

#include "../../../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( MakeNodeJump, QObject::tr( "跳" ), QObject::tr( "坐标" ) );

MakeNodeJump::MakeNodeJump( ) {
}
bool MakeNodeJump::intPortItems( MainWidget *parent ) {

	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< BoolInputPort >( "返回条件", false );
			addOutputProt< AnyOutputPort >( "继续" );
			return true;
		} );
}
