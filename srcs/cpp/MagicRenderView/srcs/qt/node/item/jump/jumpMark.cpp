#include "jumpMark.h"
#include "../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../prot/inputProt/inpInputPort/bool/boolInputPort.h"
#include "../../prot/outputProt/impOutputPort/any/anyOutputPort.h"

Imp_StaticMetaInfo( JumpMark, QObject::tr( "跳" ), QObject::tr( "坐标" ) );

JumpMark::JumpMark( ) : NodeItem( ) {
}
bool JumpMark::intPortItems( MainWidget *parent ) {

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
