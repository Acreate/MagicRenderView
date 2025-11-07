#include "generateNodeJump.h"

#include "../../../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( GenerateNodeJump, QObject::tr( "跳" ), QObject::tr( "生成" ) );

GenerateNodeJump::GenerateNodeJump( ) {
}
bool GenerateNodeJump::intPortItems( MainWidget *parent ) {

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
